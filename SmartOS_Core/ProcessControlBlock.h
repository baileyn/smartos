#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include "IOEvent.h"

#include <memory>

class ProcessControlBlock
{
public:
    explicit ProcessControlBlock(unsigned int pid, unsigned int memory);

    unsigned int pid() const;
    unsigned int cpuUsageTerm() const;
    unsigned int ioReqTerm() const;
    unsigned int waitTerm() const;
    unsigned int memory() const;

    IOEvent ioEvent() const;

private:
    unsigned int m_pid;
    unsigned int m_cpuUsageTerm;
    unsigned int m_ioReqTerm;
    unsigned int m_waitTerm;
    unsigned int m_memory;

    IOEvent m_ioEvent;
};

typedef std::unique_ptr<ProcessControlBlock> ProcessControlBlockPtr;

#endif // PROCESSCONTROLBLOCK_H
