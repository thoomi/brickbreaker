#include "application/app_play_state.h"

#include "graphics\graphics_play_state.h"

#include "gui\gui_play_state.h"

#include "logic\logic_play_state.h"

namespace Game
{
	CPlayState::CPlayState(void)
        : m_Clock()
	{
	}


	CPlayState::~CPlayState(void)
	{
	}

	bool CPlayState::InternOnEnter()
	{
        Logic::CPlayState::GetInstance().OnEnter();
		Gui::CPlayState::GetInstance().OnEnter();
        Gfx::CPlayState::GetInstance().OnEnter();

        m_Clock.Start();

		return true;
	}

	int CPlayState::InternOnRun()
	{
        m_Clock.UpdateTime();

        int NextState = Gui::CPlayState::GetInstance().OnRun();
        Logic::CPlayState::GetInstance().OnRun(m_Clock.GetElapsedTime());
        Gfx::CPlayState::GetInstance().OnRun();

        return NextState;
	}

	bool CPlayState::InternOnLeave()
	{
        Logic::CPlayState::GetInstance().OnLeave();
		Gui::CPlayState::GetInstance().OnLeave();
        Gfx::CPlayState::GetInstance().OnLeave();

		return true;
	}
} // namespace Game