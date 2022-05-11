#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include "IOEvent.h"

#include <memory>

/**
 * @brief The ProcessType enum represents the type of process
 */
enum class ProcessType { RANDOM, INTERACTIVE, CPU_BOUND, MIXED, LAST };

class ProcessControlBlock
{
public:
    explicit ProcessControlBlock(size_t pid, size_t memory);

    size_t pid() const;
    size_t cpuUsageTerm() const;
    size_t ioReqTerm() const;
    size_t waitTerm() const;
    size_t memory() const;
    size_t priority() const;

    IOEvent ioEvent() const;
    ProcessType processType() const;

    void updateCpuUsageTerm(size_t elapsed);
    void updateIoReqTerm(size_t elapsed);
    void updateWaitTerm(size_t elapsed);

    void setWaitEvent(IOEvent event);
    void clearWaitEvent();
    void setProcessType(ProcessType type);
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
