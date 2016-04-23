#pragma once

namespace Gfx
{
    class CMainMenuState
    {
        public:

            static CMainMenuState& GetInstance();

        public:

            void OnEnter();
            int  OnRun();
            void OnLeave();

        private:

            CMainMenuState(void);
            ~CMainMenuState(void);
    };
} // namespace Gfx