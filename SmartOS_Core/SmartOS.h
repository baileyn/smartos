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
        return "0.0.1";
    }

    SmartOS(unsigned long memory);

    int nextSequentialPID();

    void createProcessControlBlock(unsigned int pid, unsigned int memory);
    bool deleteProcessControlBlock(unsigned int pid);
    bool blockProcessControlBlock(unsigned int pid, IOEvent ioEvent);
    bool unblockProcessControlBlock(unsigned int pid);

    bool setActiveProcess(unsigned int pid);

    CentralProcessingUnit& cpu();

    const PCBQueue& readyQueue();
    const PCBQueue& blockedQueue();

    const ProcessControlBlockPtr& findProcessControlBlock(unsigned int pid);

    const IOEventQueue& ioEventQueue();

    size_t memory() const;

private:
    CentralProcessingUnit m_cpu;
    PCBQueue m_readyQueue;
    PCBQueue m_blockedQueue;
    IOEventQueue m_ioEventQueue;
    ProcessControlBlockPtr m_nullProcessControlBlock;

    size_t m_memory;
    size_t m_lastPid;
};

#endif // SMARTOS_H
