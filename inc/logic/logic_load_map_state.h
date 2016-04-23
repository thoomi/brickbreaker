#pragma once

namespace Logic
{
    class CLoadMapState
    {
        public:

            static CLoadMapState& GetInstance();

        public:

            void OnEnter();
            int  OnRun();
            void OnLeave();

        private:

            CLoadMapState(void);
            ~CLoadMapState(void);
    };
} // namespace Logic