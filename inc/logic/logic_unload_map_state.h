#pragma once

namespace Logic
{
    class CUnloadMapState
    {
        public:

            static CUnloadMapState& GetInstance();

        public:

            void OnEnter();
            int  OnRun();
            void OnLeave();

        private:

            CUnloadMapState(void);
            ~CUnloadMapState(void);
    };
} // namespace Logic