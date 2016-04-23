#pragma once

namespace Game
{
	class CState
	{
		public:

			enum EState
			{
				Startup = 1,
				MainMenu,
				LoadMap,
				Play,
				UnloadMap,
				Shutdown
			};

		public:

			CState(void);
			virtual ~CState(void);

		public:

			bool OnEnter();
			int  OnRun();
			bool OnLeave();

		private:

			virtual bool InternOnEnter() = 0;
			virtual int  InternOnRun()   = 0;
			virtual bool InternOnLeave() = 0;
	};
} // namespace Game