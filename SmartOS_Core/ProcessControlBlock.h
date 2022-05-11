#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include "IOEvent.h"

#include <memory>

class ProcessControlBlock
{
public:
    explicit ProcessControlBlock(size_t pid, size_t memory);

    size_t pid() const;
    size_t cpuUsageTerm() const;
    size_t ioReqTerm() const;
    size_t waitTerm() const;
    size_t memory() const;

    IOEvent ioEvent() const;

private:
    size_t m_pid;
    size_t m_cpuUsageTerm;
    size_t m_ioReqTerm;
    size_t m_waitTerm;
    size_t m_memory;

    IOEvent m_ioEvent;
};

typedef std::unique_ptr<ProcessControlBlock> ProcessControlBlockPtr;

#endif // PROCESSCONTROLBLOCK_H
