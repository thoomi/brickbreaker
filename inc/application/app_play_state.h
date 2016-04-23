#pragma once

#include "app_state.h"

#include "core/core_clock.h"

namespace Game
{
	class CPlayState : public CState
	{
		public:

			CPlayState(void);
			~CPlayState(void);

			virtual bool InternOnEnter();
			virtual int  InternOnRun();
			virtual bool InternOnLeave();

        private:

            Core::CClock m_Clock;
	};
} // namespace Game