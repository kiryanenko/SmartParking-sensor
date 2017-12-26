#include "Timer.h"

#include <Arduino.h>

Timer::Timer() : m_startTime(0), m_finishTime(0), m_isOverflow(false)
{
}

void Timer::start(const unsigned long period)
{
    m_startTime = millis();
    m_finishTime = m_startTime + period;
    m_isOverflow = m_startTime > m_finishTime;
}

bool Timer::isFinished() const
{
    const auto now = millis();
    if (m_isOverflow) {
        return now < m_startTime && m_finishTime <= now;
    }

    return m_finishTime <= now;
}

Timer::~Timer()
{
}
