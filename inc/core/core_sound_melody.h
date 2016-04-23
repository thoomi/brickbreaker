#pragma once

#include "core_sound_note.h"

#include <vector>

namespace Core
{
namespace Sound
{
    class CMelody
    {
        public:

            typedef std::vector<CNote> CNoteContainer;

        public:

            CMelody();

        public:

            void AddNote(unsigned int _Frequency, unsigned int _Duration);

        public:

            void Play();
            void Abort();

        private:

            CNoteContainer m_Notes;
            bool           m_ShouldAbort;
    };

} // namespace Sound
} // namespace Core