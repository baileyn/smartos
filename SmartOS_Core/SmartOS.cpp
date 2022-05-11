#include "SmartOS.h"

SmartOS::SmartOS(size_t memory)
    : m_memory{memory}, m_lastPid{0}
{}

size_t SmartOS::nextSequentialPID()
{
    for (;; m_lastPid++) {
        if (findProcessControlBlock(m_lastPid) == nullptr) {
            return m_lastPid;
        }
    }

    return -1;
}

void SmartOS::createProcessControlBlock(size_t pid, size_t memory)
{
    // TODO: Check for already existing pid.
    auto pcb = std::make_unique<ProcessControlBlock>(pid, memory);
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
        m_readyQueue.push_back(std::move(oldActive));

        return true;
    }

    return false;
}

CentralProcessingUnit& SmartOS::cpu()
{
    return m_cpu;
}

const PCBQueue& SmartOS::readyQueue()
{
    return m_readyQueue;
}

const PCBQueue& SmartOS::blockedQueue()
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

size_t SmartOS::memory() const
{
    return m_memory;
}
