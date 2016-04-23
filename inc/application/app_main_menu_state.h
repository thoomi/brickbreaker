#pragma once

#include "app_state.h"

namespace Game
{
	class CMainMenuState : public CState
	{
		public:

			CMainMenuState(void);
			~CMainMenuState(void);

			virtual bool InternOnEnter();
			virtual int  InternOnRun();
			virtual bool InternOnLeave();
	};
} // namespace Game