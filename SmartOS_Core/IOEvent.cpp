#include "IOEvent.h"

IOEvent::IOEvent(Type type, unsigned long cycleStamp)
    : m_type{type}, m_cycleStamp{cycleStamp}
{

}

IOEvent::Type IOEvent::type() const
{
    return m_type;
}

unsigned long IOEvent::cycleStamp() const
{
    return m_cycleStamp;
}
