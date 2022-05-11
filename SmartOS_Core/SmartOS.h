#ifndef SMARTOS_H
#define SMARTOS_H

#include "Global.h"

#include "ProcessControlBlock.h"

#include <vector>

class SMARTOS_CORESHARED_EXPORT SmartOS
{
public:
    static inline std::string getVersionNumber() {
        return "0.0.1";
    }

    void createProcessControlBlock(const std::string& name, unsigned int pid, unsigned int memory);

public:
    SmartOS();

private:
    std::vector<ProcessControlBlockPtr> m_readyList;
};

#endif // SMARTOS_H
