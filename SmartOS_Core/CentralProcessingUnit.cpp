#include "CentralProcessingUnit.h"

CentralProcessingUnit::CentralProcessingUnit()
{}

ProcessControlBlockPtr CentralProcessingUnit::setActiveProcess(ProcessControlBlockPtr pcb)
{
    ProcessControlBlockPtr current = std::move(m_currentProcess);
    m_currentProcess = std::move(pcb);
    return std::move(current);
}

ProcessControlBlockPtr& CentralProcessingUnit::currentProcess()
{
    return m_currentProcess;
}
