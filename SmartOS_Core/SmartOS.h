#ifndef SMARTOS_H
#define SMARTOS_H

#include "Global.h"

#include <QVersionNumber>

class SMARTOS_CORESHARED_EXPORT SmartOS
{
public:
    static inline QVersionNumber getVersionNumber() {
        return QVersionNumber(0, 0, 1);
    }

public:
    SmartOS();
};

#endif // SMARTOS_H
