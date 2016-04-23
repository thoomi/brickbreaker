#include "gui/gui_event_manager.h"

namespace Gui
{
    CEventManager::CEventManager()
        : m_Listeners()
    {
    }

    CEventManager::CEventManager(const CEventManager&)
        : m_Listeners()
    {
    }

    CEventManager& CEventManager::GetInstance()
    {
        static CEventManager s_Instance;

        return s_Instance;
    }

    void CEventManager::RegisterListener(CEventListener* _pListener)
    {
        m_Listeners.push_back(_pListener);
    }

    void CEventManager::UnregisterListener(CEventListener* _pListener)
    {
        auto ListenerIteratorEnd = m_Listeners.end();

        for (auto ListenerIterator = m_Listeners.begin(); ListenerIterator != ListenerIteratorEnd; ++ ListenerIterator)
        {
            if (*ListenerIterator == _pListener)
            {
                m_Listeners.erase(ListenerIterator);
                break;
            }
        }
    }

    void CEventManager::OnInputEvent(const Core::CUserEvent& _rEvent)
    {
        // -----------------------------------------------------------------------------
        // Dispatch the incoming event to all registered listeners.
        // -----------------------------------------------------------------------------
        for (auto&& Listener : m_Listeners)
        {
            Listener->OnEvent(_rEvent);
        }
    }
} // namespace Gui

