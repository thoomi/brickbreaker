#include "application/app_shutdown_state.h"

namespace Game
{
	CShutdownState::CShutdownState(void)
	{
	}


	CShutdownState::~CShutdownState(void)
	{
	}

	bool CShutdownState::InternOnEnter()
	{
		return true;
	}

	int CShutdownState::InternOnRun()
	{
		return 1;
	}

	bool CShutdownState::InternOnLeave()
	{
		return true;
	}
} // namespace Game