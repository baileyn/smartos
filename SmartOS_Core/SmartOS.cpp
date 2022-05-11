#include "SmartOS.h"

#include <random>

#include <iostream>

namespace
{
std::random_device r;
std::mt19937 engine(r());
} // namespace

SmartOS::SmartOS(size_t memory)
    : m_maxMemory{memory}
    , m_lastPid{1}
    , m_scheduler{SchedulerType::DEFAULT}
    , m_lastSwitch{0}
{
    addOperatingSystemProcess();
}

size_t SmartOS::nextSequentialPID()
{
    for (;; m_lastPid++) {
        if (findProcessControlBlock(m_lastPid) == nullptr) {
            return m_lastPid;
        }
    }

    return -1;
}

void SmartOS::createProcessControlBlock(size_t pid, size_t memory, ProcessType type)
{
    // TODO: Check for already existing pid.
    auto pcb = std::make_unique<ProcessControlBlock>(pid, memory);

    while (type == ProcessType::RANDOM) {
        std::uniform_int_distribution<int> gen{0, static_cast<int>(ProcessType::LAST) - 1};

        type = static_cast<ProcessType>(gen(engine));
    }

    pcb->setProcessType(type);
    m_readyQueue.push_back(std::move(pcb));
}

bool SmartOS::deleteProcessControlBlock(size_t pid)
{
    if (m_cpu.currentProcess()->pid() == pid) {
        m_cpu.setActiveProcess(nullptr);
        return true;
    }

    auto idx = std::find_if(
        std::begin(m_readyQueue), std::end(m_readyQueue),
        [pid](ProcessControlBlockPtr& pcb) { return pcb->pid() == pid; });
    if (idx != m_readyQueue.end()) {
        m_readyQueue.erase(idx);
        return true;
    }

    idx = std::find_if(
        std::begin(m_blockedQueue), std::end(m_blockedQueue),
        [pid](ProcessControlBlockPtr& pcb) { return pcb->pid() == pid; });
    if (idx != m_blockedQueue.end()) {
        m_blockedQueue.erase(idx);
        return true;
    }

    return false;
}

bool SmartOS::blockProcessControlBlock(size_t pid, IOEvent ioEvent)
{
    Q_UNUSED(ioEvent);

    if (m_cpu.currentProcess()->pid() == pid) {
        // Remove the process from the CPU
        auto oldActive = m_cpu.setActiveProcess(nullptr);

        // Move the PCB to the Blocked Queue
        m_blockedQueue.push_back(std::move(oldActive));

        return true;
    }

    auto idx = std::find_if(
        std::begin(m_readyQueue), std::end(m_readyQueue),
        [pid](ProcessControlBlockPtr& pcb) { return pcb->pid() == pid; });
    if (idx != m_readyQueue.end()) {
        // Grab the pointer from the list.
        auto pcb = std::move(*idx);

        // Remove the now invalidated unique_ptr.
        m_readyQueue.erase(idx);

        // Add the proces to the Blocked Queue
        m_blockedQueue.push_back(std::move(pcb));

        return true;
    }

    return false;
}

bool SmartOS::unblockProcessControlBlock(size_t pid)
{
    auto idx = std::find_if(
        std::begin(m_blockedQueue), std::end(m_blockedQueue),
        [pid](ProcessControlBlockPtr& pcb) { return pcb->pid() == pid; });
    if (idx != m_blockedQueue.end()) {
        // Grab the pointer from the list.
        auto pcb = std::move(*idx);

        // Remove the now invalidated unique_ptr.
        m_blockedQueue.erase(idx);

        // Add the proces to the Ready Queue
        m_readyQueue.push_back(std::move(pcb));

        return true;
    }

    return false;
}

void SmartOS::addEvent(IOEvent::Type type)
{
    m_ioEventQueue.push_back(IOEvent(type, m_cycles));
}

bool SmartOS::setActiveProcess(size_t pid)
{
    // We can only move a process to the CPU if it was currently in the
    // ready queue.

    auto idx = std::find_if(
        std::begin(m_readyQueue), std::end(m_readyQueue),
        [pid](ProcessControlBlockPtr& pcb) { return pcb->pid() == pid; });

    if (idx != m_readyQueue.end()) {
        // Grab the pointer from the list.
        auto pcb = std::move(*idx);

        // Remove the now invalidated unique_ptr.
        m_readyQueue.erase(idx);

        // Set the new active process.
        auto oldActive = std::move(m_cpu.setActiveProcess(std::move(pcb)));

        if (oldActive != nullptr) {
            m_readyQueue.push_back(std::move(oldActive));
        }

        return true;
    }

    return false;
}

void SmartOS::moveActiveToReady()
{
    m_readyQueue.push_back(m_cpu.setActiveProcess(nullptr));
}

void SmartOS::moveActiveToBlocked(IOEvent::Type type)
{
    m_cpu.currentProcess()->setWaitEvent(IOEvent(type, m_cycles));
    m_blockedQueue.push_back(m_cpu.setActiveProcess(nullptr));
}

CentralProcessingUnit& SmartOS::cpu()
{
    return m_cpu;
}

PCBQueue& SmartOS::readyQueue()
{
    return m_readyQueue;
}

PCBQueue& SmartOS::blockedQueue()
{
    return m_blockedQueue;
}

const ProcessControlBlockPtr& SmartOS::findProcessControlBlock(size_t pid)
{
    if (cpu().currentProcess() != nullptr && cpu().currentProcess()->pid() == pid) {
        return cpu().currentProcess();
    } else {
        auto idx = std::find_if(std::begin(readyQueue()), std::end(readyQueue()),
                                [pid](const ProcessControlBlockPtr& pcb) {
                                    return pcb->pid() == pid;
                                });

        if (idx != std::end(readyQueue())) {
            return *idx;
        }

        idx = std::find_if(std::begin(blockedQueue()), std::end(blockedQueue()),
                           [pid](const ProcessControlBlockPtr& pcb) {
                               return pcb->pid() == pid;
                           });

        if (idx != std::end(blockedQueue())) {
            return *idx;
        }
    }

    return m_nullProcessControlBlock;
}

const IOEventQueue& SmartOS::ioEventQueue()
{
    return m_ioEventQueue;
}

size_t SmartOS::usedMemory()
{
    size_t memoryUsed = 0;

    for (auto& pcb : readyQueue()) {
        if (pcb != nullptr) {
            memoryUsed += pcb->memory();
        }
    }

    for (auto& pcb : blockedQueue()) {
        if (pcb != nullptr) {
            memoryUsed += pcb->memory();
        }
    }

    if (cpu().currentProcess() != nullptr) {
        memoryUsed += cpu().currentProcess()->memory();
    }

    return memoryUsed;
}

void SmartOS::updateCurrentProcessControlBlock()
{
    ProcessControlBlockPtr current = nullptr;

    switch (m_scheduler) {
    case SchedulerType::DEFAULT: {
        if (m_readyQueue.empty()) {
            // Keep the current process in the cpu.
            return;
        }

        current = std::move(m_readyQueue.front());
        m_readyQueue.erase(m_readyQueue.begin());
        break;
    }

    case SchedulerType::ROUND_ROBIN: {
        if (m_cycles - m_lastSwitch < m_timeQuantum && m_cpu.currentProcess() != nullptr) {
            return;
        }

        if (m_readyQueue.empty()) {
            return;
        }

        auto ptr = std::move(m_readyQueue.front());
        m_readyQueue.erase(m_readyQueue.begin());

        current = std::move(ptr);

        m_lastSwitch = m_cycles;
        break;
    }
    default:
        std::cout << "Can't handle scheduler." << std::endl;
    }

    if (current != nullptr) {
        ProcessControlBlockPtr oldActive = m_cpu.setActiveProcess(std::move(current));

        // 10 second penalty
        adjustProcessTimes(10);

        // Move the old process into the ready queue if it exists.
        if (oldActive != nullptr) {
            m_readyQueue.push_back(std::move(oldActive));
        }
    }
}

void SmartOS::addOperatingSystemProcess()
{
    // Add OS process.
    createProcessControlBlock(0, 0);
    setActiveProcess(0);
}

void SmartOS::adjustProcessTimes(size_t elapsed)
{
    m_cpu.currentProcess()->updateCpuUsageTerm(elapsed);

    for (auto& pcb : m_readyQueue) {
        pcb->updateWaitTerm(elapsed);
    }

    for (auto& pcb : m_blockedQueue) {
        pcb->updateIoReqTerm(elapsed);
    }
}

void SmartOS::execute()
{
    // Determine if we have anything to actually do.
    if (m_blockedQueue.size() == 0 && m_readyQueue.size() == 1 &&
        m_cpu.currentProcess() == nullptr) {
        return;
    }

    m_cycles++;

    std::uniform_int_distribution<size_t> processingGen(0, 10000);
    adjustProcessTimes(processingGen(engine));

    // Every 2 time cycles, generate a random number between 0 and 10.
    if (m_cycles % 2 == 0) {
        std::uniform_int_distribution<size_t> eventGenerator(0, 10);

        size_t operation = eventGenerator(engine);

        if (operation == 4) {
            std::cout << "User IO Event" << std::endl;
            addEvent(IOEvent::Type::USER_IO);
        } else if (operation == 9) {
            std::cout << "Hard Drive event" << std::endl;
            addEvent(IOEvent::Type::HARD_DRIVE);
        }
    }

    if (m_cpu.currentProcess()->pid() != 0) {
        std::vector<int> options = {0, 1, 2, 3};

        if (m_cpu.currentProcess()->processType() == ProcessType::INTERACTIVE) {
            // 3 times more likely
            for (int i = 0; i < 3; i++) {
                options.push_back(2);
            }
        } else if (m_cpu.currentProcess()->processType() == ProcessType::CPU_BOUND) {
            for (int i = 0; i < 3; i++) {
                // If we make the other options 3 times as likely, then waiting
                // for the hard drive will be 3 times less likely.
                options.push_back(0);
                options.push_back(1);
                options.push_back(3);
            }
        }

        std::uniform_int_distribution<size_t> resultGen(0, options.size() - 1);

        size_t operation = options.at(resultGen(engine));

        switch (operation) {
        case 0:
            std::cout << "TERMINATE" << std::endl;
            // Terminate process.
            m_cpu.setActiveProcess(nullptr);
            break;
        case 1:
            // Ready queue
            moveActiveToReady();
            break;
        case 2:
            // Block for User IO
            moveActiveToBlocked(IOEvent::Type::USER_IO);
            std::cout << "Move to blocked awiting for user IO" << std::endl;
            break;
        case 3:
            // Block for Hard drive
            std::cout << "Move to blocked waiting for hard drive." << std::endl;
            moveActiveToBlocked(IOEvent::Type::HARD_DRIVE);
            break;
        default:
            // TODO: Report error.
            std::cout << "ERROR ERROR ERROR: " << operation << std::endl;
            break;
        }
    }

    for (auto& event : ioEventQueue()) {
        auto i = m_blockedQueue.begin();
        while (i != m_blockedQueue.end()) {
            if ((*i)->ioEvent().type() == event.type()) {
                if ((*i)->ioEvent().cycleStamp() < event.cycleStamp()) {
                    (*i)->clearWaitEvent();
                    m_readyQueue.push_back(std::move(*i));
                    m_blockedQueue.erase(i);
                    break;
                }
            }

            i++;
        }
    }
}

size_t SmartOS::cycleCount() const
{
    return m_cycles;
}

void SmartOS::reset()
{
    m_cycles = 0;
    m_readyQueue.clear();
    m_blockedQueue.clear();
    m_cpu.setActiveProcess(nullptr);

    addOperatingSystemProcess();
}

void SmartOS::setScheduler(SchedulerType type)
{
    m_scheduler = type;
}

void SmartOS::setTimeQuantum(size_t quantum)
{
    m_timeQuantum = quantum;
}

size_t SmartOS::maxMemory() const
{
    return m_maxMemory;
}
