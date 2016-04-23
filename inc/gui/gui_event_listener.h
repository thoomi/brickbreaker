#pragma once

#include "core/core_event.h"

namespace Gui
{
    class CEventListener
    {
        public:

            virtual void OnEvent(const Core::CUserEvent& _rEvent) = 0;

        public:

            inline CEventListener();
            inline virtual ~CEventListener();
    };
} // namespace Gui

namespace Gui
{
    CEventListener::CEventListener()
    {
        
    }

    CEventListener::~CEventListener()
    {
        
    }
} // namespace Gui