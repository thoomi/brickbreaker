#pragma once

namespace Gfx
{
    class CPlayState
    {
        public:

            static CPlayState& GetInstance();

        public:

            void OnEnter();
            int  OnRun();
            void OnLeave();

        private:

            CPlayState(void);
            ~CPlayState(void);
    };
} // namespace Gfx