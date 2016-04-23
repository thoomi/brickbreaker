#include "application/app_load_map_state.h"

#include "graphics/graphics_load_map_state.h"

#include "logic\logic_load_map_state.h"

namespace Game
{
	CLoadMapState::CLoadMapState(void)
	{
	}

	CLoadMapState::~CLoadMapState(void)
	{
	}

	bool CLoadMapState::InternOnEnter()
	{
		Logic::CLoadMapState::GetInstance().OnEnter();
        Gfx::CLoadMapState::GetInstance().OnEnter();

		return true;
	}

	int CLoadMapState::InternOnRun()
	{
        Logic::CLoadMapState::GetInstance().OnRun();
        Gfx::CLoadMapState::GetInstance().OnRun();

		return CState::Play;
	}

	bool CLoadMapState::InternOnLeave()
	{
        Logic::CLoadMapState::GetInstance().OnLeave();
        Gfx::CLoadMapState::GetInstance().OnLeave();

		return true;
	}
} // namespace Game