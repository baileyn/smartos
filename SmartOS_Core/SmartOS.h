#ifndef SMARTOS_H
#define SMARTOS_H

#include "Global.h"

#include "CentralProcessingUnit.h"
#include "IOEvent.h"
#include "ProcessControlBlock.h"

#include <list>

#include <fstream>

/**
 * @brief PCBQueue a data structure used to iterate proceses.
 */
typedef std::list<ProcessControlBlockPtr> PCBQueue;

/**
 * @brief IOEventQueue a data structure used to iterate IO events.
 */
typedef std::list<IOEvent> IOEventQueue;

/**
 * @brief The SchedulerType enum represents the different types of process schedulers.
 */
enum class SchedulerType {
    DEFAULT,
    ROUND_ROBIN,
    MLFQ,
};

/**
 * @brief The SmartOS class is the heart of the SmartOS operating system simulator. All functions to manipulate processes are found here.
 */
class SMARTOS_CORESHARED_EXPORT SmartOS
{
public:
    /**
     * @brief getVersionNumber returns the version number
     * @return the version number
     */
    static inline std::string getVersionNumber()
    {
        return "0.3.3";
    }

    /**
     * @brief SmartOS construct a new simulator with the specified maximum memory.
     * @param memory the maximum amount of memory
     */
    SmartOS(size_t memory);

    /**
     * @brief nextSequentialPID the next process id that is available starting from 0.
     * @return the next process id
     */
    size_t nextSequentialPID();

    /**
     * @brief createProcessControlBlock creates a new Process Control Block and adds it to the ready queue.
     * @param pid the pid
     * @param memory the amount of memory needed for the processes
     * @param type the type of process.
     */
    void createProcessControlBlock(size_t pid, size_t memory, ProcessType type = ProcessType::RANDOM);

    /**
     * @brief deleteProcessControlBlock deletes the process control block with the specified pid.
     * @param pid the process's id
     * @return true if successful
     */
    bool deleteProcessControlBlock(size_t pid);

    /**
     * @brief blockProcessControlBlock moves the specified process to the block queue
     * @param pid the process's id
     * @param ioEvent the event that being waited on
     * @return true if successful
     */
    bool blockProcessControlBlock(size_t pid, IOEvent ioEvent);

    /**
     * @brief unblockProcessControlBlock removes the process from the block queue and inserts it into the ready queue
     * @param pid the process's id
     * @return true if successful
     */
    bool unblockProcessControlBlock(size_t pid);

    /**
     * @brief setActiveProcess sets the active process to the process with the specified pid.
     * @param pid the process's pid
     * @return true if successful
     */
    bool setActiveProcess(size_t pid);

    /**
     * @brief cpu returns a reference to the Central Processing Unit.
     * @return a reference to the Central Processing Unit
     */
    CentralProcessingUnit& cpu();

    /**
     * @brief readyQueue returns a reference to the Ready Queue
     * @return a reference to the Ready Queue
     */
    PCBQueue& readyQueue();

    /**
     * @brief blockedQueue returns a reference to the Blocked Queue
     * @return a reference to the Blocked Queue
     */
    PCBQueue& blockedQueue();

    /**
     * @brief findProcessControlBlock finds a reference to the Process Control Block with the specified id.
     * @param pid the process's id
     * @return a reference to the Process Control Block if found, otherwise a null pcb.
     */
    const ProcessControlBlockPtr& findProcessControlBlock(size_t pid);

    /**
     * @brief ioEventQueue returns a reference to the io event queue
     * @return a reference to the io event queue
     */
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

    /**
     * @brief determineNextProcess determines the next process in the ready queue to run.
     * @return the next process in the ready queue to run.
     */
    ProcessControlBlockPtr determineNextProcess();

    /**
     * @brief cycleCount returns the current time cycle count
     * @return the current time cycle count
     */
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

    /**
     * @brief setMaximumPriority sets the maximum priority level.
     * @param priority the priority level
     */
    void setMaximumPriority(size_t priority);

private:
    /**
     * @brief moveActiveToReady moves the active process to the Ready Queue.
     */
    void moveActiveToReady();

    /**
     * @brief moveActiveToBlocked moves the active process to the Blocked Queue waiting for an event of the specified type.
     * @param type the type of IOEvent to wait for
     */
    void moveActiveToBlocked(IOEvent::Type type);

    /**
     * @brief adjustProcessTimes adjusts the waiting times for all of the processes
     * @param elapsed the number of time cycles that have elapsed
     */
    void adjustProcessTimes(size_t elapsed);

    /**
     * @brief addEvent adds the specified IOEvent to the queue.
     * @param type the type of IO event that occured
     */
    void addEvent(IOEvent::Type type);

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

    size_t m_maxPriority;

    size_t m_lastSwitch;
    size_t m_timeQuantum;

    std::ofstream m_output;
};

#endif // SMARTOS_H
