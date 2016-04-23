#include "application/app_game_state.h"


CGameState::CGameState(void)
{
}


CGameState::~CGameState(void)
{
}

bool CGameState::InternOnEnter()
{
	return true;
}

int CGameState::InternOnRun()
{
	return 1;
}

bool CGameState::InternOnLeave()
{
	return true;
}
