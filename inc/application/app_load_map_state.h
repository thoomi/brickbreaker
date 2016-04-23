#pragma once

#include "app_state.h"

namespace Game
{
	class CLoadMapState : public CState
	{
		public:

			CLoadMapState(void);
			~CLoadMapState(void);

			virtual bool InternOnEnter();
			virtual int  InternOnRun();
			virtual bool InternOnLeave();
	};
} // namespace Game