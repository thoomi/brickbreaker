#include "core/core_clock.h"

#include <Windows.h>

namespace Core
{
    CClock::CClock()
        : m_Frequency          (0.0)
        , m_TimeSinceLastUpdate(0.0f)
        , m_LastTick           (0)
        , m_StartTick          (0)
    {
        long long Frequency;
        
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&Frequency));

        m_Frequency = static_cast<double>(Frequency);
    }

    CClock::~CClock()
    {

    }

    void CClock::Start()
    {
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_StartTick));
        m_LastTick = m_StartTick;
    }

    void CClock::UpdateTime()
    {
        long long CurrentTick;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentTick));

        m_TimeSinceLastUpdate = static_cast<float>((CurrentTick - m_LastTick) / m_Frequency);
        m_LastTick            = CurrentTick;
    }

    float CClock::GetElapsedTime()
    {
        return m_TimeSinceLastUpdate;
    }
}