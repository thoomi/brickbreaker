#include "core/core_event.h"

namespace Core
{
    CUserEvent::CUserEvent(unsigned int _Type, unsigned int _Key)
    {
        m_Bits.m_Action = 0;
        m_Bits.m_Type   = _Type;
        m_Bits.m_Key    = _Key;
    }

    CUserEvent::CUserEvent(unsigned int _Type, unsigned int _Action, unsigned int _Key)
    {
        m_Bits.m_Action = _Action;
        m_Bits.m_Type   = _Type;
        m_Bits.m_Key    = _Key;
    }

    CUserEvent::~CUserEvent()
    {
    }

    CUserEvent::EType CUserEvent::GetType() const
    { 
        return static_cast<EType>(m_Bits.m_Type);
    }

    CUserEvent::EAction CUserEvent::GetAction() const
    {
        return static_cast<EAction>(m_Bits.m_Action);
    }

    CUserEvent::EKey CUserEvent::GetKey() const
    {
        return static_cast<EKey>(m_Bits.m_Key);
    }
} // namespace Core