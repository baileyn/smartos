#ifndef SMARTOS_H
#define SMARTOS_H

#include "Global.h"

#include "CentralProcessingUnit.h"
#include "IOEvent.h"
#include "ProcessControlBlock.h"

#include <list>

typedef std::list<ProcessControlBlockPtr> PCBQueue;
typedef std::list<IOEventPtr> IOEventQueue;

class SMARTOS_CORESHARED_EXPORT SmartOS
{
public:
    static inline std::string getVersionNumber()
    {
        return "0.0.4";
    }

    SmartOS(size_t memory);

    size_t nextSequentialPID();

    void createProcessControlBlock(size_t pid, size_t memory);
    bool deleteProcessControlBlock(size_t pid);
    bool blockProcessControlBlock(size_t pid, IOEvent ioEvent);
    bool unblockProcessControlBlock(size_t pid);

    bool setActiveProcess(size_t pid);

    CentralProcessingUnit& cpu();

    PCBQueue& readyQueue();
    PCBQueue& blockedQueue();

    const ProcessControlBlockPtr& findProcessControlBlock(size_t pid);

    const IOEventQueue& ioEventQueue();

    /**
     * @brief maxMemory returns the maximum amount of memory in the operating system.
     * @return the maximum amount of memory in the operating system
     */
    size_t maxMemory() const;

    /**
     * @brief memory returns the amount of memory used in the operating system.
     * @return the amount of memory used in the operating system
     */
    size_t usedMemory();

private:
    CentralProcessingUnit m_cpu;
    PCBQueue m_readyQueue;
    PCBQueue m_blockedQueue;
    IOEventQueue m_ioEventQueue;
    ProcessControlBlockPtr m_nullProcessControlBlock;

    size_t m_maxMemory;
    size_t m_lastPid;
};

#endif // SMARTOS_H
