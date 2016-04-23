#pragma once

#include "core/core_sound.h"

#include "gui/gui_element_number.h"
#include "gui/gui_event_listener.h"

namespace Gui
{
    class CPlayState : CEventListener
    {
        public:

            static CPlayState& GetInstance();

        public:

            virtual void OnEvent(const Core::CUserEvent& _rEvent) override;

        public:

            void OnEnter();
            int  OnRun();
            void OnLeave();

        private:

            CPlayState(void);
            ~CPlayState(void);

        private:

            Core::Sound::CMusicPlayer m_MusicPlayer;
            CGuiNumber::SharedPtr     m_pBrickCounter;
            int                       m_NextStateID;
    };
} // namespace Gui