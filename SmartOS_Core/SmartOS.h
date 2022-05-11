#ifndef SMARTOS_H
#define SMARTOS_H

#include "Global.h"

#include "CentralProcessingUnit.h"
#include "IOEvent.h"
#include "ProcessControlBlock.h"

#include <vector>

typedef std::vector<ProcessControlBlockPtr> PCBQueue;
typedef std::vector<IOEventPtr> IOEventQueue;

class SMARTOS_CORESHARED_EXPORT SmartOS
{
public:
    static inline std::string getVersionNumber() {
        return "0.0.1";
    }

    SmartOS(unsigned long memory);
    void createProcessControlBlock(unsigned int pid, unsigned int memory);
    CentralProcessingUnit& cpu();

    const PCBQueue& readyQueue();
    const PCBQueue& blockedQueue();
    const IOEventQueue& ioEventQueue();

private:
    CentralProcessingUnit m_cpu;
    PCBQueue m_readyQueue;
    PCBQueue m_blockedQueue;
    IOEventQueue m_ioEventQueue;

    unsigned long m_memory;
};

#endif // SMARTOS_H
