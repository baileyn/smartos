#include "IOEvent.h"

IOEvent::IOEvent(Type type, size_t cycleStamp)
    : m_type{type}
    , m_cycleStamp{cycleStamp}
{}

IOEvent::Type IOEvent::type() const
{
    return m_type;
}

size_t IOEvent::cycleStamp() const
{
    return m_cycleStamp;
}
