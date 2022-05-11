#include "CentralProcessingUnit.h"

CentralProcessingUnit::CentralProcessingUnit()
{

}

void CentralProcessingUnit::setActiveProcess(ProcessControlBlockPtr pcb)
{
    m_currentProcess = std::move(pcb);
}

ProcessControlBlockPtr &CentralProcessingUnit::currentProcess()
{
    return m_currentProcess;
}
