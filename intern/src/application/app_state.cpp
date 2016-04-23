#include "application/app_state.h"

namespace Game
{
	CState::CState(void)
	{
	}


	CState::~CState(void)
	{
	}

	bool CState::OnEnter()
	{
		return InternOnEnter();
	}

	int CState::OnRun()
	{
		return InternOnRun();
	}

	bool CState::OnLeave()
	{
		return InternOnLeave();
	}
} // namespace Game