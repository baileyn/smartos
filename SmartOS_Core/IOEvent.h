#ifndef IOEVENT_H
#define IOEVENT_H

#include <memory>

class IOEvent
{
public:
    /**
     * @brief The Type enum represents the different types of IOEvents.
     */
    enum class Type {
        NONE,
        HARD_DRIVE,
        USER_IO,
    };

public:
    /**
     * @brief IOEvent constructs a new IOEvent with the specified type and cycleStamp
     * @param type the type of IOEvent
     * @param cycleStamp the time cycle this event was added
     */
    IOEvent(Type type, size_t cycleStamp);

    /**
     * @brief type returns the type of event
     * @return  the type of event
     */
    Type type() const;

    /**
     * @brief cycleStamp returns the time cycle this event was added.
     * @return the time cycle this event was added
     */
    size_t cycleStamp() const;

private:
    Type m_type;
    size_t m_cycleStamp;
};

#endif // IOEVENT_H
