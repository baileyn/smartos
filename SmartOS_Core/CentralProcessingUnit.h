#ifndef CENTRALPROCESSINGUNIT_H
#define CENTRALPROCESSINGUNIT_H

#include "ProcessControlBlock.h"

class CentralProcessingUnit
{
public:
    CentralProcessingUnit();

    void setActiveProcess(ProcessControlBlockPtr pcb);
    ProcessControlBlockPtr& currentProcess();

private:
    ProcessControlBlockPtr m_currentProcess;
};

#endif // CENTRALPROCESSINGUNIT_H
