#pragma once

#include "app_state.h"

namespace Game
{
	class CStartupState : public CState
	{
		public:

			CStartupState(void);
			~CStartupState(void);

			virtual bool InternOnEnter();
			virtual int  InternOnRun();
			virtual bool InternOnLeave();
	};
} // namespace Game