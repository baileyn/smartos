#ifndef IOEVENT_H
#define IOEVENT_H

#include <memory>

class IOEvent
{
public:
    enum class Type {
        NONE,
        HARD_DRIVE,
        USER_IO,
    };

public:
    IOEvent(Type type, size_t cycleStamp);
    Type type() const;
    size_t cycleStamp() const;

private:
    Type m_type;
    size_t m_cycleStamp;
};

#endif // IOEVENT_H
