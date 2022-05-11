#ifndef SMARTOS_H
#define SMARTOS_H

#include "Global.h"

#include "CentralProcessingUnit.h"
#include "IOEvent.h"
#include "ProcessControlBlock.h"

#include <list>

typedef std::list<ProcessControlBlockPtr> PCBQueue;
typedef std::list<IOEvent> IOEventQueue;

enum class SchedulerType {
    DEFAULT,
    ROUND_ROBIN,
    MLFQ,
};

class SMARTOS_CORESHARED_EXPORT SmartOS
{
public:
    static inline std::string getVersionNumber()
    {
        return "0.0.4";
    }

    SmartOS(size_t memory);

    size_t nextSequentialPID();

    void createProcessControlBlock(size_t pid, size_t memory, ProcessType type = ProcessType::RANDOM);
    bool deleteProcessControlBlock(size_t pid);
    bool blockProcessControlBlock(size_t pid, IOEvent ioEvent);
    bool unblockProcessControlBlock(size_t pid);

    void addEvent(IOEvent::Type type);

    bool setActiveProcess(size_t pid);

    void moveActiveToReady();
    void moveActiveToBlocked(IOEvent::Type type);

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

    /**
     * @brief execute execute a single step in the operating system.
     */
    void execute();

    /**
     * @brief updateCurrent sets the next active process in the CPU.
     */
    void updateCurrentProcessControlBlock();

    /**
     * @brief addOperatingSystemProcess adds the operating system process
     */
    void addOperatingSystemProcess();

    void adjustProcessTimes(size_t elapsed);

    /**
     * @brief determineNextProcess determines the next process in the ready queue to run.
     * @return the next process in the ready queue to run.
     */
    ProcessControlBlockPtr determineNextProcess();

    size_t cycleCount() const;

    /**
     * @brief reset resets the operating system.
     */
    void reset();

    /**
     * @brief setScheduler sets the type of scheduler to use.
     * @param type the scheduler type
     */
    void setScheduler(SchedulerType type);

    /**
     * @brief setTimeQuantum sets the time quantum
     * @param quantum the time quantum
     */
    void setTimeQuantum(size_t quantum);

private:
    CentralProcessingUnit m_cpu;
    PCBQueue m_readyQueue;
    PCBQueue m_blockedQueue;
    IOEventQueue m_ioEventQueue;
    ProcessControlBlockPtr m_nullProcessControlBlock;

    size_t m_maxMemory;
    size_t m_lastPid;

    size_t m_cycles;

    SchedulerType m_scheduler;

    size_t m_lastSwitch;
    size_t m_timeQuantum;
};

#endif // SMARTOS_H
