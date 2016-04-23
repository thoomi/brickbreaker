#pragma once

#include "app_state.h"

namespace Game
{
	class CShutdownState : public CState
	{
		public:

			CShutdownState(void);
			~CShutdownState(void);

			virtual bool InternOnEnter();
			virtual int  InternOnRun();
			virtual bool InternOnLeave();
	};
} // namespace Game