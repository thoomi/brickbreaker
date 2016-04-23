#pragma once

#include "app_state.h"

namespace Game
{
	class CUnloadMapState : public CState
	{
		public:

			CUnloadMapState(void);
			~CUnloadMapState(void);

			virtual bool InternOnEnter();
			virtual int  InternOnRun();
			virtual bool InternOnLeave();
	};
} // namespace Game