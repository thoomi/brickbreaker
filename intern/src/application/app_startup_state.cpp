#include "application/app_startup_state.h"

namespace Game
{
	CStartupState::CStartupState(void)
	{
	}


	CStartupState::~CStartupState(void)
	{
	}

	bool CStartupState::InternOnEnter()
	{
		return true;
	}

	int CStartupState::InternOnRun()
	{
		return CState::MainMenu;
	}

	bool CStartupState::InternOnLeave()
	{
		return true;
	}
} // namespace Game
