#include "application/app_unload_map_state.h"

#include "logic/logic_unload_map_state.h"

namespace Game
{
	CUnloadMapState::CUnloadMapState(void)
	{
	}


	CUnloadMapState::~CUnloadMapState(void)
	{
	}

	bool CUnloadMapState::InternOnEnter()
	{
        Logic::CUnloadMapState::GetInstance().OnEnter();

		return true;
	}

	int CUnloadMapState::InternOnRun()
	{
        Logic::CUnloadMapState::GetInstance().OnRun();

		return CState::MainMenu;
	}

	bool CUnloadMapState::InternOnLeave()
	{
        Logic::CUnloadMapState::GetInstance().OnLeave();

		return true;
	}
} // namespace Game