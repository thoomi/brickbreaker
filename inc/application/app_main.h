#pragma once

#include "app_load_map_state.h"
#include "app_main_menu_state.h"
#include "app_play_state.h"
#include "app_shutdown_state.h"
#include "app_startup_state.h"
#include "app_unload_map_state.h"

#include <Windows.h>

namespace Game
{
	class CApplication
	{
		public:

			CApplication(void);
			~CApplication(void);

            void OnStart();
			void OnRun();
            void OnExit();

			bool OnTransition(CState& _rState);

        public:
            
            void OnInputEvent(const INPUT_RECORD& _rRecord);

        private:

            void* m_pInputConsoleHandle;

		private:

			CState* m_pCurrentState;

		private:

			CPlayState      m_PlayState;
			CLoadMapState   m_LoadMapState;
			CMainMenuState  m_MainMenuState;
			CStartupState   m_StartupState;
			CShutdownState  m_ShutdownState;
			CUnloadMapState m_UnloadMapState;
	};
} // namespace Game