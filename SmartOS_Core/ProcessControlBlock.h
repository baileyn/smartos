#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include "IOEvent.h"

#include <memory>

/**
 * @brief The ProcessType enum represents the type of process
 */
enum class ProcessType { RANDOM, INTERACTIVE, CPU_BOUND, MIXED, LAST };

/**
 * @brief The ProcessControlBlock class represents a Process Control BLock in the simulator.
 */
class ProcessControlBlock
{
public:
    /**
     * @brief ProcessControlBlock constructs a new Process Control Block with the specified pid and memory required.
     * @param pid the id of the process
     * @param memory the amount of memory needed by the process
     */
    explicit ProcessControlBlock(size_t pid, size_t memory);

    /**
     * @brief pid returns the process's id
     * @return the process's id
     */
    size_t pid() const;

    /**
     * @brief cpuUsageTerm returns the time spent using the cpu
     * @return the time spent using the cpu
     */
    size_t cpuUsageTerm() const;

    /**
     * @brief ioReqTerm returns the time waiting for IO
     * @return the time waiting for IO
     */
    size_t ioReqTerm() const;

    /**
     * @brief waitTerm returns the time waiting in the ready queue
     * @return the time waiting in the ready queue
     */
    size_t waitTerm() const;

    /**
     * @brief memory returns the memory required by the process
     * @return the memory required by the process
     */
    size_t memory() const;

    /**
     * @brief priority returns the priority for this process
     * @return the priority of the process
     */
    size_t priority() const;

    /**
     * @brief ioEvent returns the type of IOEvent that the process is waiting on.
     * @return the type of IOEvent the process is waiting on
     */
    IOEvent ioEvent() const;

    /**
     * @brief processType returns the type of process this is
     * @return the type of process this is
     */
    ProcessType processType() const;

    /**
     * @brief updateCpuUsageTerm adds the elapsed time to the cpu usage.
     * @param elapsed the time elapsed
     */
    void updateCpuUsageTerm(size_t elapsed);

    /**
     * @brief updateIoReqTerm adds the elapsed time to the io waiting time
     * @param elapsed the time elapsed
     */
    void updateIoReqTerm(size_t elapsed);

    /**
     * @brief updateWaitTerm adds the elapsed time to the time waiting in the ready queue.
     * @param elapsed the time elapsed
     */
    void updateWaitTerm(size_t elapsed);

    /**
     * @brief setWaitEvent sets the type of event this process is waiting for
     * @param event the type of event this process is waiting for
     */
    void setWaitEvent(IOEvent event);

    /**
     * @brief clearWaitEvent clears the event this process is waiting for
     */
    void clearWaitEvent();

    /**
     * @brief setProcessType sets the type of process this is
     * @param type the type of process this is
     */
    void setProcessType(ProcessType type);

    /**
     * @brief setPriority sets this process's priority
     * @param priority the new priority
     */
    void setPriority(size_t priority);

private:
    size_t m_pid;
    size_t m_cpuUsageTerm;
    size_t m_ioReqTerm;
    size_t m_waitTerm;
    size_t m_memory;
    size_t m_priority;

    IOEvent m_ioEvent;
    ProcessType m_type;
};

typedef std::unique_ptr<ProcessControlBlock> ProcessControlBlockPtr;

#endif // PROCESSCONTROLBLOCK_H
