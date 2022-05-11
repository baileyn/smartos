#include "ProcessControlBlock.h"

ProcessControlBlock::ProcessControlBlock(unsigned int pid, unsigned int memory)
    : m_pid{pid}, m_cpuUsageTerm{0}, m_ioReqTerm{0}, m_waitTerm{0}, m_memory{memory}
{

}

unsigned int ProcessControlBlock::pid() const
{
    return m_pid;
}

unsigned int ProcessControlBlock::cpuUsageTerm() const
{
    return m_cpuUsageTerm;
}

unsigned int ProcessControlBlock::ioReqTerm() const
{
    return m_ioReqTerm;
}

unsigned int ProcessControlBlock::waitTerm() const
{
    return m_waitTerm;
}

unsigned int ProcessControlBlock::memory() const
{
    return m_memory;
}
