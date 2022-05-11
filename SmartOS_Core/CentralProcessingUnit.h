#ifndef CENTRALPROCESSINGUNIT_H
#define CENTRALPROCESSINGUNIT_H

#include "ProcessControlBlock.h"

/**
 * @brief The CentralProcessingUnit class holds the current process
 */
class CentralProcessingUnit
{
public:
    /**
     * @brief CentralProcessingUnit construct a new Central Processing Unit
     */
    CentralProcessingUnit();

    /**
     * @brief setActiveProcess sets the active process
     * @param pcb the process to make active
     * @return the old process that was in the CPU, or nullptr
     */
    ProcessControlBlockPtr setActiveProcess(ProcessControlBlockPtr pcb);

    /**
     * @brief currentProcess returns a reference to the current process.
     * @return a reference to the current process
     */
    ProcessControlBlockPtr& currentProcess();

private:
    ProcessControlBlockPtr m_currentProcess;
};

#endif // CENTRALPROCESSINGUNIT_H
