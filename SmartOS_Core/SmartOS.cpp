#include "SmartOS.h"

SmartOS::SmartOS(unsigned long memory)
    : m_memory{memory}
{

}

void SmartOS::createProcessControlBlock(unsigned int pid, unsigned int memory)
{
    // TODO: Check for already existing pid.
    auto pcb = std::make_unique<ProcessControlBlock>(pid, memory);
    m_readyQueue.push_back(std::move(pcb));
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
