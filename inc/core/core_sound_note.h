#pragma once

namespace Core
{
namespace Sound
{
    class CNote
    {
         public:

            enum EFrequency 
            {
                Rest = 0,
                C1  = 131,    CS1 = 139,    D1  = 147,    DS1 = 156,    E1  = 165,    F1 = 175,
                FS1 = 185,    G1  = 196,    GS1 = 208,    A1  = 220,    AS1 = 233,    B1 = 247,
                C2  = 262,    CS2 = 277,    D2  = 294,    DS2 = 311,    E2  = 330,    F2 = 349,
                FS2 = 370,    G2  = 392,    GS2 = 415,    A2  = 440,    AS2 = 466,    B2 = 494,
                C3  = 523,    CS3 = 554,    D3  = 587,    DS3 = 622,    E3  = 659,    F3 = 698,
                FS3 = 740,    G3  = 784,    GS3 = 830,    A3  = 880,    AS3 = 932,    B3 = 988,
            };

            enum EDuration 
            {
                Sixteenth = 180, 
                Eighth    = (Sixteenth << 1),
                Quart     = (Eighth    << 1),
                Half      = (Quart     << 1), 
                Whole     = (Half      << 1)
            };

        public:

            CNote(EFrequency _Frequency, EDuration _Duration);

        public:

            void Play();

        private:

            EFrequency m_Frequency;
            EDuration  m_Duration;
    };

} // namespace Sound
} // namespace Core