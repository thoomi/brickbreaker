#pragma once

#include "core/core_event.h"

#include "gui/gui_event_listener.h"

#include <vector>

namespace Gui
{
    class CEventManager
    {
        public:
            
            typedef std::vector<CEventListener*> CListenerContainer;

        public:

            static CEventManager& GetInstance();

        public:

            void RegisterListener(CEventListener* _pListener);
            void UnregisterListener(CEventListener* _pListener);

        public:

            void OnInputEvent(const Core::CUserEvent& _rEvent);

        private:

            CEventManager();
            CEventManager(const CEventManager&);

        private:

            CListenerContainer m_Listeners;
    };
} // namespace Gui