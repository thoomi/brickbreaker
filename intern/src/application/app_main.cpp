#include "application/app_main.h"

#include "core/core_event.h"

#include "gui/gui_event_manager.h"

namespace Game
{
	CApplication::CApplication(void)
        : m_pInputConsoleHandle(nullptr)
        , m_pCurrentState      (nullptr)
        , m_PlayState          ()
        , m_LoadMapState       ()
        , m_MainMenuState      ()
        , m_StartupState       ()
        , m_ShutdownState      ()
        , m_UnloadMapState     ()
	{
	}


	CApplication::~CApplication(void)
	{
	}

    void CApplication::OnStart()
    {
        m_pInputConsoleHandle = GetStdHandle(STD_INPUT_HANDLE); 

        if (m_pInputConsoleHandle == INVALID_HANDLE_VALUE)
        {
            throw "Failed to retrieve console input handle.";
        }

        SetConsoleMode(m_pInputConsoleHandle, ENABLE_WINDOW_INPUT);

        if (m_pInputConsoleHandle == INVALID_HANDLE_VALUE)
        {
            throw "Failed to enable window input mode.";
        }
    }

	void CApplication::OnRun()
	{
		m_StartupState.OnEnter();
		m_pCurrentState = &m_StartupState;

        // -----------------------------------------------------------------------------
        // We will collect a maximum of 5 events per loop run.
        // -----------------------------------------------------------------------------
        const DWORD  MaxNumberOfEventsPerCycle = 5;
        INPUT_RECORD InputRecords[MaxNumberOfEventsPerCycle];

        for (;;)
		{
            // -----------------------------------------------------------------------------
            // Collect any incoming user events and queue them up in the event handler.
            // -----------------------------------------------------------------------------
            DWORD NumberOfReadEvents = 0;
            PeekConsoleInput(m_pInputConsoleHandle, InputRecords, MaxNumberOfEventsPerCycle, &NumberOfReadEvents);

            for (unsigned long IndexOfEvent = 0; IndexOfEvent < NumberOfReadEvents; IndexOfEvent++)
            {
                 OnInputEvent(InputRecords[IndexOfEvent]);
            }

            FlushConsoleInputBuffer(m_pInputConsoleHandle); 

            // -----------------------------------------------------------------------------
            // Run the state machine, while a return value of the states OnRun method means
            // either to stay in the current one or switch to another state. The return 
            // value 0 will indicate to stay.
            // -----------------------------------------------------------------------------
			switch (m_pCurrentState->OnRun())
			{
				case 0:
					break;

				case CState::Startup:
					OnTransition(m_StartupState);
					break;

				case CState::LoadMap:
					OnTransition(m_LoadMapState);
					break;

				case CState::MainMenu:
					OnTransition(m_MainMenuState);
					break;

				case CState::Play:
					OnTransition(m_PlayState);
					break;

				case CState::UnloadMap:
					OnTransition(m_UnloadMapState);
					break;

				case CState::Shutdown:
                    return;
			}
		}
	}

    void CApplication::OnExit()
    {
        if (m_pCurrentState != nullptr)
        {
            m_pCurrentState->OnLeave();
        }
        
        m_ShutdownState.OnEnter();
        m_ShutdownState.OnRun();
        m_ShutdownState.OnLeave();
    }

	bool CApplication::OnTransition(CState& _rState)
	{
		if (m_pCurrentState->OnLeave() == false)
		{
			return false;
		}

		m_pCurrentState = &_rState;

		return m_pCurrentState->OnEnter();
	}

    void CApplication::OnInputEvent(const INPUT_RECORD& _rRecord)
	{
        if (_rRecord.EventType != KEY_EVENT)
        {
            return;
        }

        Core::CUserEvent::EAction KeyAction = _rRecord.Event.KeyEvent.bKeyDown ? Core::CUserEvent::KeyPressed : Core::CUserEvent::KeyReleased;
	
        Core::CUserEvent Event = Core::CUserEvent(Core::CUserEvent::Input, KeyAction, _rRecord.Event.KeyEvent.wVirtualKeyCode);

        Gui::CEventManager::GetInstance().OnInputEvent(Event);
    }
} // namespace Game