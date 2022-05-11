#include "ProcessControlBlock.h"

ProcessControlBlock::ProcessControlBlock(size_t pid, size_t memory)
    : m_pid{pid}
    , m_cpuUsageTerm{0}
    , m_ioReqTerm{0}
    , m_waitTerm{0}
    , m_memory{memory}
    , m_ioEvent{IOEvent::Type::NONE, 0}
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

void ProcessControlBlock::updateCpuUsageTerm(size_t elapsed)
{
    m_cpuUsageTerm += elapsed;
}

void ProcessControlBlock::updateWaitTerm(size_t elapsed)
{
    m_waitTerm += elapsed;
}
