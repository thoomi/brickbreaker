#include "core/core_sound.h"

#include <thread>

namespace Core
{
namespace Sound
{
    CMusicPlayer::CMusicPlayer()
        : m_ThreadShouldTerminate(false)
        , m_CurrentSong(ESong::SilentNight)
        , m_Songs()
    {
        InitializeSongs();
    }

    CMusicPlayer::~CMusicPlayer()
    {
        
    }

    void CMusicPlayer::SetSong(ESong _Song)
    {
        m_CurrentSong = _Song;
    }

    void CMusicPlayer::Play()
    {
        m_Songs[m_CurrentSong].Play();
    }

    void CMusicPlayer::PlayLoop()
    {
        while (!m_ThreadShouldTerminate)
        {
            m_Songs[m_CurrentSong].Play();
        }
    }


    void CMusicPlayer::PlayInBackground()
    {
        m_ThreadShouldTerminate = false;

        std::thread PlayThread(&CMusicPlayer::PlayLoop, this);
        PlayThread.detach();
    }

    void CMusicPlayer::Stop()
    {
        m_ThreadShouldTerminate = true;
        m_Songs[m_CurrentSong].Abort();
    }

    void CMusicPlayer::InitializeSongs()
    {
        // -----------------------------------------------------------------------------
        // Setup Silent Night
        // -----------------------------------------------------------------------------
        CMelody& rSilentNight = m_Songs[SilentNight];

        rSilentNight.AddNote(CNote::A2,   CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::B2,   CNote::Sixteenth);
        rSilentNight.AddNote(CNote::A2,   CNote::Eighth);
        rSilentNight.AddNote(CNote::FS2,  CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::A2,   CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::B2,   CNote::Sixteenth);
        rSilentNight.AddNote(CNote::A2,   CNote::Eighth);
        rSilentNight.AddNote(CNote::FS2,  CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::E3,   CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::DS2,  CNote::Sixteenth);
        rSilentNight.AddNote(CNote::E3,   CNote::Eighth);
        rSilentNight.AddNote(CNote::CS3,  CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::D3,   CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::CS3,  CNote::Sixteenth);
        rSilentNight.AddNote(CNote::D3,   CNote::Eighth);
        rSilentNight.AddNote(CNote::A2,   CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::B2, CNote::Quart);
        rSilentNight.AddNote(CNote::B2, CNote::Eighth);
        rSilentNight.AddNote(CNote::D3, CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::C3, CNote::Sixteenth);
        rSilentNight.AddNote(CNote::B2, CNote::Eighth);

        rSilentNight.AddNote(CNote::A2,   CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::B2,   CNote::Sixteenth);
        rSilentNight.AddNote(CNote::A2,   CNote::Eighth);
        rSilentNight.AddNote(CNote::FS2,  CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::B2,  CNote::Quart);
        rSilentNight.AddNote(CNote::B2,  CNote::Eighth);
        rSilentNight.AddNote(CNote::D3,  CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::CS3, CNote::Sixteenth);
        rSilentNight.AddNote(CNote::B2,  CNote::Eighth);

        rSilentNight.AddNote(CNote::A2,   CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::B2,   CNote::Sixteenth);
        rSilentNight.AddNote(CNote::A2,   CNote::Eighth);
        rSilentNight.AddNote(CNote::FS2,  CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::CS3, CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::CS3, CNote::Sixteenth);
        rSilentNight.AddNote(CNote::CS3, CNote::Eighth);
        rSilentNight.AddNote(CNote::E3,  CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::D3,  CNote::Sixteenth);
        rSilentNight.AddNote(CNote::CS3, CNote::Eighth);

        rSilentNight.AddNote(CNote::D3,   CNote::Quart + CNote::Eighth);
        rSilentNight.AddNote(CNote::FS3,  CNote::Quart);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);

        rSilentNight.AddNote(CNote::D3,  CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::A2,  CNote::Sixteenth);
        rSilentNight.AddNote(CNote::FS2, CNote::Eighth);
        rSilentNight.AddNote(CNote::A2,  CNote::Eighth + CNote::Sixteenth);
        rSilentNight.AddNote(CNote::G2,  CNote::Sixteenth);
        rSilentNight.AddNote(CNote::E2,  CNote::Eighth);

        rSilentNight.AddNote(CNote::D2,   CNote::Half + CNote::Eighth);
        rSilentNight.AddNote(CNote::Rest, CNote::Eighth);



        // -----------------------------------------------------------------------------
        // Setup Imperial march
        // -----------------------------------------------------------------------------
        CMelody& rImperialMarch = m_Songs[ImperialMarch];

        rImperialMarch.AddNote(440, 500);
        rImperialMarch.AddNote(440, 500);
        rImperialMarch.AddNote(440, 500);
        rImperialMarch.AddNote(349, 350);
        rImperialMarch.AddNote(523, 150);
                          
        rImperialMarch.AddNote(440, 500);
        rImperialMarch.AddNote(349, 350);
        rImperialMarch.AddNote(523, 150);
        rImperialMarch.AddNote(440, 1000);
                          
        rImperialMarch.AddNote(659, 500);
        rImperialMarch.AddNote(659, 500);
        rImperialMarch.AddNote(659, 500);
        rImperialMarch.AddNote(698, 350);
        rImperialMarch.AddNote(523, 150);
                          
        rImperialMarch.AddNote(415, 500);
        rImperialMarch.AddNote(349, 350);
        rImperialMarch.AddNote(523, 150);
        rImperialMarch.AddNote(440, 1000);
                          
        rImperialMarch.AddNote(880, 500);
        rImperialMarch.AddNote(440, 350);
        rImperialMarch.AddNote(440, 150);
        rImperialMarch.AddNote(880, 500);
        rImperialMarch.AddNote(830, 250);
        rImperialMarch.AddNote(784, 250);
                          
        rImperialMarch.AddNote(740, 125);
        rImperialMarch.AddNote(698, 125);
        rImperialMarch.AddNote(740, 250);
                          
        rImperialMarch.AddNote(455, 250);
        rImperialMarch.AddNote(622, 500);
        rImperialMarch.AddNote(587, 250);
        rImperialMarch.AddNote(554, 250);
                          
        rImperialMarch.AddNote(523, 125);
        rImperialMarch.AddNote(466, 125);
        rImperialMarch.AddNote(523, 250);
                          
        rImperialMarch.AddNote(349, 125);
        rImperialMarch.AddNote(415, 500);
        rImperialMarch.AddNote(349, 375);
        rImperialMarch.AddNote(440, 125);
                          
        rImperialMarch.AddNote(523, 500);
        rImperialMarch.AddNote(440, 375);
        rImperialMarch.AddNote(523, 125);
        rImperialMarch.AddNote(659, 1000);
                          
        rImperialMarch.AddNote(880, 500);
        rImperialMarch.AddNote(440, 350);
        rImperialMarch.AddNote(440, 150);
        rImperialMarch.AddNote(880, 500);
        rImperialMarch.AddNote(830, 250);
        rImperialMarch.AddNote(784, 250);
                          
        rImperialMarch.AddNote(740, 125);
        rImperialMarch.AddNote(698, 125);
        rImperialMarch.AddNote(740, 250);
                          
        rImperialMarch.AddNote(455, 250);
        rImperialMarch.AddNote(622, 500);
        rImperialMarch.AddNote(587, 250);
        rImperialMarch.AddNote(554, 250);
                          
        rImperialMarch.AddNote(523, 125);
        rImperialMarch.AddNote(466, 125);
        rImperialMarch.AddNote(523, 250);
                          
        rImperialMarch.AddNote(349, 250);
        rImperialMarch.AddNote(415, 500);
        rImperialMarch.AddNote(349, 375);
        rImperialMarch.AddNote(523, 125);
                          
        rImperialMarch.AddNote(440, 500);
        rImperialMarch.AddNote(349, 375);
        rImperialMarch.AddNote(261, 125);
        rImperialMarch.AddNote(440, 1000);


        // -----------------------------------------------------------------------------
        // Setup Mission Impossible
        // -----------------------------------------------------------------------------
        CMelody& rMissionImpossible = m_Songs[MissionImpossible];

        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(932, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(1047, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(699, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(740, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(932, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(1047, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(0, 300);
        rMissionImpossible.AddNote(699, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(740, 150);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(932, 150);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(587, 1200);
        rMissionImpossible.AddNote(0, 75);
        rMissionImpossible.AddNote(932, 150);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(554, 1200);
        rMissionImpossible.AddNote(0, 75);
        rMissionImpossible.AddNote(932, 150);
        rMissionImpossible.AddNote(784, 150);
        rMissionImpossible.AddNote(523, 1200);
        rMissionImpossible.AddNote(0, 150);
        rMissionImpossible.AddNote(466, 150);
        rMissionImpossible.AddNote(523, 150);

        // -----------------------------------------------------------------------------
        // Setup Super Mario
        // -----------------------------------------------------------------------------
        CMelody& rSuperMario = m_Songs[SuperMario];

        rSuperMario.AddNote(659, 250);
        rSuperMario.AddNote(659, 250);
        rSuperMario.AddNote(659, 300);
        rSuperMario.AddNote(523, 250);
        rSuperMario.AddNote(659, 250);
        rSuperMario.AddNote(784, 300);
        rSuperMario.AddNote(392, 300);
        rSuperMario.AddNote(523, 275);
        rSuperMario.AddNote(392, 275);
        rSuperMario.AddNote(330, 275);
        rSuperMario.AddNote(440, 250);
        rSuperMario.AddNote(494, 250);
        rSuperMario.AddNote(466, 275);
        rSuperMario.AddNote(440, 275);
        rSuperMario.AddNote(392, 275);
        rSuperMario.AddNote(659, 250);
        rSuperMario.AddNote(784, 250);
        rSuperMario.AddNote(880, 275);
        rSuperMario.AddNote(698, 275);
        rSuperMario.AddNote(784, 225);
        rSuperMario.AddNote(659, 250);
        rSuperMario.AddNote(523, 250);
        rSuperMario.AddNote(587, 225);
        rSuperMario.AddNote(494, 225);


        // -----------------------------------------------------------------------------
        // Setup Pink panther
        // -----------------------------------------------------------------------------
        CMelody& rPinkPanther = m_Songs[PinkPanther];

        rPinkPanther.AddNote(233, 250);
        rPinkPanther.AddNote(246, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 1800);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(233, 250);
        rPinkPanther.AddNote(246, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 1800);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(246, 250);
        rPinkPanther.AddNote(246, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(246, 250);
        rPinkPanther.AddNote(220, 1800);
        rPinkPanther.AddNote(220, 900);
        rPinkPanther.AddNote(220, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(233, 250);
        rPinkPanther.AddNote(246, 450);
        rPinkPanther.AddNote(0, 250);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 1800);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(0, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(293, 250);
        rPinkPanther.AddNote(329, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 675);
        rPinkPanther.AddNote(293, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(493, 250);
        rPinkPanther.AddNote(392, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(392, 250);
        rPinkPanther.AddNote(369, 900);
        rPinkPanther.AddNote(392, 150);
        rPinkPanther.AddNote(349, 150);
        rPinkPanther.AddNote(329, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(246, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(0, 787);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(293, 250);
        rPinkPanther.AddNote(329, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 675);
        rPinkPanther.AddNote(293, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(493, 250);
        rPinkPanther.AddNote(392, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(587, 250);
        rPinkPanther.AddNote(554, 1800);
        rPinkPanther.AddNote(554, 900);
        rPinkPanther.AddNote(0, 787);
        rPinkPanther.AddNote(277, 250);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(293, 250);
        rPinkPanther.AddNote(329, 450);
        rPinkPanther.AddNote(0, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(261, 675);
        rPinkPanther.AddNote(293, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(493, 250);
        rPinkPanther.AddNote(392, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(392, 250);
        rPinkPanther.AddNote(369, 900);
        rPinkPanther.AddNote(392, 150);
        rPinkPanther.AddNote(349, 150);
        rPinkPanther.AddNote(329, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(246, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(0, 1350);
        rPinkPanther.AddNote(587, 675);
        rPinkPanther.AddNote(523, 250);
        rPinkPanther.AddNote(392, 675);
        rPinkPanther.AddNote(349, 250);
        rPinkPanther.AddNote(329, 675);
        rPinkPanther.AddNote(261, 250);
        rPinkPanther.AddNote(369, 250);
        rPinkPanther.AddNote(349, 675);
        rPinkPanther.AddNote(369, 250);
        rPinkPanther.AddNote(349, 675);
        rPinkPanther.AddNote(369, 250);
        rPinkPanther.AddNote(349, 675);
        rPinkPanther.AddNote(369, 250);
        rPinkPanther.AddNote(349, 675);
        rPinkPanther.AddNote(329, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(246, 150);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(0, 900);
        rPinkPanther.AddNote(329, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(246, 150);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(261, 900);
        rPinkPanther.AddNote(0, 900);
        rPinkPanther.AddNote(329, 150);
        rPinkPanther.AddNote(261, 150);
        rPinkPanther.AddNote(246, 150);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(261, 450);
        rPinkPanther.AddNote(261, 900);



        // -----------------------------------------------------------------------------
        // Setup Mario Theme
        // -----------------------------------------------------------------------------
        CMelody& rMarioTheme = m_Songs[MarioTheme];

        rMarioTheme.AddNote(1480, 200);
        rMarioTheme.AddNote(1568, 200);
        rMarioTheme.AddNote(1568, 200);
        rMarioTheme.AddNote(1568, 200);

        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);

        rMarioTheme.AddNote(369, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(369, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(392, 400);
        rMarioTheme.AddNote(196, 400);

        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(830, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(987, 400);

        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(830, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(987, 400);
        rMarioTheme.AddNote(0, 200);

        rMarioTheme.AddNote(1108, 10);
        rMarioTheme.AddNote(1174, 200);
        rMarioTheme.AddNote(1480, 10);
        rMarioTheme.AddNote(1568, 200);

        rMarioTheme.AddNote(0, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(830, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(987, 400);

        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(698, 200);

        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(784, 200);
        rMarioTheme.AddNote(880, 400);
        rMarioTheme.AddNote(784, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(659, 200);

        rMarioTheme.AddNote(587, 200);
        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(784, 400);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(587, 200);

        rMarioTheme.AddNote(523, 200);
        rMarioTheme.AddNote(587, 200);
        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(698, 400);
        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(587, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(523, 200);

        rMarioTheme.AddNote(0, 400);
        rMarioTheme.AddNote(349, 400);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(329, 200);
        rMarioTheme.AddNote(523, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(466, 200);

        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(523, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(1760, 200);
        rMarioTheme.AddNote(440, 200);

        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(1568, 200);
        rMarioTheme.AddNote(392, 200);

        rMarioTheme.AddNote(349, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(415, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(1396, 200);
        rMarioTheme.AddNote(349, 200);

        rMarioTheme.AddNote(329, 200);
        rMarioTheme.AddNote(311, 200);
        rMarioTheme.AddNote(329, 200);
        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(698, 400);
        rMarioTheme.AddNote(783, 400);

        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(523, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(880, 200);
        rMarioTheme.AddNote(1760, 200);
        rMarioTheme.AddNote(440, 200);

        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(493, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(1568, 200);
        rMarioTheme.AddNote(392, 200);

        rMarioTheme.AddNote(349, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(440, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(659, 200);
        rMarioTheme.AddNote(698, 200);
        rMarioTheme.AddNote(739, 200);
        rMarioTheme.AddNote(783, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(392, 200);
        rMarioTheme.AddNote(196, 200);
        rMarioTheme.AddNote(196, 200);
        rMarioTheme.AddNote(196, 200);

        rMarioTheme.AddNote(185, 200);
        rMarioTheme.AddNote(196, 200);
        rMarioTheme.AddNote(185, 200);
        rMarioTheme.AddNote(196, 200);
        rMarioTheme.AddNote(207, 200);
        rMarioTheme.AddNote(220, 200);
        rMarioTheme.AddNote(233, 200);
        rMarioTheme.AddNote(246, 200);
    }

} // namespace Sound
} // namespace Core