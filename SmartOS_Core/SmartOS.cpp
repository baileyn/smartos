#include "SmartOS.h"

SmartOS::SmartOS()
{
}

void SmartOS::createProcessControlBlock(const std::string& name, unsigned int pid, unsigned int memory)
{
    // TODO: Check for already existing pid.
    auto pcb = std::make_unique<ProcessControlBlock>(name, pid, memory);
    m_readyList.push_back(std::move(pcb));
}
