#include "ProcessControlBlock.h"

ProcessControlBlock::ProcessControlBlock(size_t pid, size_t memory)
    : m_pid{pid}
    , m_cpuUsageTerm{0}
    , m_ioReqTerm{0}
    , m_waitTerm{0}
    , m_memory{memory}
    , m_priority{0}
    , m_ioEvent{IOEvent::Type::NONE, 0}
    , m_type{ProcessType::MIXED}
{}

size_t ProcessControlBlock::pid() const
{
    return m_pid;
}

size_t ProcessControlBlock::cpuUsageTerm() const
{
    return m_cpuUsageTerm;
}

size_t ProcessControlBlock::ioReqTerm() const
{
    return m_ioReqTerm;
}

size_t ProcessControlBlock::waitTerm() const
{
    return m_waitTerm;
}

size_t ProcessControlBlock::memory() const
{
    return m_memory;
}

size_t ProcessControlBlock::priority() const
{
    return m_priority;
}

IOEvent ProcessControlBlock::ioEvent() const
{
    return m_ioEvent;
}

ProcessType ProcessControlBlock::processType() const
{
    return m_type;
}

void ProcessControlBlock::updateCpuUsageTerm(size_t elapsed)
{
    m_cpuUsageTerm += elapsed;
}

void ProcessControlBlock::updateIoReqTerm(size_t elapsed)
{
    m_ioReqTerm += elapsed;
}

void ProcessControlBlock::updateWaitTerm(size_t elapsed)
{
    m_waitTerm += elapsed;
}

void ProcessControlBlock::setWaitEvent(IOEvent event)
{
    m_ioEvent = event;
}

void ProcessControlBlock::clearWaitEvent()
{
    m_ioEvent = IOEvent(IOEvent::Type::NONE, 0);
}

void ProcessControlBlock::setProcessType(ProcessType type)
{
    m_type = type;
}

void ProcessControlBlock::setPriority(size_t priority)
{
    m_priority = priority;
}
