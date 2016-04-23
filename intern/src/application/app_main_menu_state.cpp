#include "application/app_main_menu_state.h"

#include "graphics/graphics_main_menu_state.h"

#include "gui/gui_main_menu_state.h"

namespace Game
{
	CMainMenuState::CMainMenuState(void)
	{
	}


	CMainMenuState::~CMainMenuState(void)
	{
	}

	bool CMainMenuState::InternOnEnter()
	{
        Gui::CMainMenuState::GetInstance().OnEnter();
        Gfx::CMainMenuState::GetInstance().OnEnter();
		return true;
	}

	int CMainMenuState::InternOnRun()
	{
        int NextState = Gui::CMainMenuState::GetInstance().OnRun();
        Gfx::CMainMenuState::GetInstance().OnRun();

		return NextState;
	}

	bool CMainMenuState::InternOnLeave()
	{
        Gui::CMainMenuState::GetInstance().OnLeave();
        Gfx::CMainMenuState::GetInstance().OnLeave();

		return true;
	}
} // namespace Game