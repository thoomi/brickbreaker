#include "core/core_sound_melody.h"

namespace Core
{
namespace Sound
{
    CMelody::CMelody()
        : m_Notes()
        , m_ShouldAbort(false)
    {
    }

    void CMelody::AddNote(unsigned int _Frequency, unsigned int _Duration)
    {
        m_Notes.push_back(CNote(static_cast<CNote::EFrequency>(_Frequency), static_cast<CNote::EDuration>(_Duration)));
    }

    void CMelody::Play()
    {
        for (auto& Note : m_Notes)
        {
            if (m_ShouldAbort)
            {
                m_ShouldAbort = false;
                break;
            }
            Note.Play();
        }
    }

    void CMelody::Abort()
    {
        m_ShouldAbort = true;
    }


} // namespace Sound
} // namespace Core