#pragma once

#include "gui/gui_event_listener.h"
#include "gui/gui_element_options_list.h"

namespace Gui
{
    class CMainMenuState : CEventListener
    {
        public:

            static CMainMenuState& GetInstance();

        public:

            virtual void OnEvent(const Core::CUserEvent& _rEvent) override;

        public:

            void OnEnter();
            int  OnRun();
            void OnLeave();

        private:

            CMainMenuState(void);
            ~CMainMenuState(void);

        private:

            int                     m_NextStateID;
            COptionsList::SharedPtr m_OptionsList;
    };
} // namespace Gui