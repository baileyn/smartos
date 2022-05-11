#ifndef IOEVENT_H
#define IOEVENT_H

#include <memory>

class IOEvent
{
public:
    enum class Type {
        HARD_DRIVE,
        USER_IO,
    };

public:
    IOEvent(Type type, unsigned long cycleStamp);
    Type type() const;
    unsigned long cycleStamp() const;

private:
    Type m_type;
    unsigned long m_cycleStamp;
};

typedef std::unique_ptr<IOEvent> IOEventPtr;

#endif // IOEVENT_H
