#include "logic/logic_command_queue.h"

namespace Logic
{
    CCommandQueue& CCommandQueue::GetInstance()
    {
        static CCommandQueue s_Instance;

        return s_Instance;
    }

    CCommandQueue::CCommandQueue()
        : m_Commands()
    {
    }

    CCommandQueue::~CCommandQueue()
    {
    }

    void CCommandQueue::AddCommand(const CCommand& _rCommand)
    {
        m_Commands.push(_rCommand);
    }

    const CCommand& CCommandQueue::GetNextCommand()
    {
        return m_Commands.front();
    }

    void CCommandQueue::PopCommand()
    {
        m_Commands.pop();
    }

    bool CCommandQueue::HasCommand()
    {
        return !m_Commands.empty();
    }
} // namespace Logic