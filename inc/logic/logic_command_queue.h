#pragma once

#include "logic/logic_command.h"

#include <queue>

namespace Logic
{
    class CCommandQueue
    {
        public:

            static CCommandQueue& GetInstance();

        public:

            void AddCommand(const CCommand& _rCommand);
            const CCommand& GetNextCommand();
            void PopCommand();
            bool HasCommand();

        private:

            CCommandQueue(void);
            ~CCommandQueue(void);

        private:

            std::queue<CCommand> m_Commands;
    };
} // namespace Logic