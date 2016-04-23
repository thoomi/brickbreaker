#pragma once

#include "logic/logic_command.h"

namespace Logic
{
    class CPlayState
    {
        public:

            static CPlayState& GetInstance();

        public:

            void OnEnter();
            int  OnRun(float _ElapsedTime);
            void OnLeave();

        private:

            void ProcessMoveCommand(const CCommand& _rCommand);
            void ProcessActionCommand(const CCommand& _rCommand);

        private:

            CPlayState(void);
            ~CPlayState(void);
    };
} // namespace Logic