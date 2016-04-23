#pragma once

#include "core_sound_melody.h"

namespace Core
{
namespace Sound
{
    class CMusicPlayer
    {
        public:

            enum ESong
            {
                SilentNight,
                ImperialMarch,
                MissionImpossible,
                SuperMario,
                PinkPanther,
                MarioTheme,
                NumberOfSongs
            };

        public:

            CMusicPlayer();
            ~CMusicPlayer();

        public:
            
            void SetSong(ESong _Song);

        public:

            void Play();
            void PlayInBackground();

            void Stop();
            
        private:

            void PlayLoop();

        private:

            void InitializeSongs();

        private:

            bool m_ThreadShouldTerminate;

        private:

            ESong   m_CurrentSong;
            CMelody m_Songs[NumberOfSongs];
    };

} // namespace Sound
} // namespace Core