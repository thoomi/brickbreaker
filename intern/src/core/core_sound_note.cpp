#include "core/core_sound_note.h"

#include <Windows.h>

namespace Core
{
namespace Sound
{
    CNote::CNote(EFrequency _Frequency, EDuration _Duration)
        : m_Frequency(_Frequency)
        , m_Duration(_Duration)
    {
    }

    void CNote::Play()
    {
        if (m_Frequency != EFrequency::Rest)
        {
            Beep(m_Frequency, m_Duration);
        }
        else
        {
            Sleep(m_Duration);
        }
    }

} // namespace Sound
} // namespace Core