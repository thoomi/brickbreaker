#include "logic/logic_command.h"

namespace Logic
{
    CCommand::CCommand()
        : m_Type            (EType::Undefined)
        , m_pEntity         (nullptr)
        , m_MovingDirection ()
    {
    }

    CCommand::EType CCommand::GetType() const
    {
        return m_Type;
    }

    void CCommand::SetType(EType _Type)
    {
        m_Type = _Type;
    }


    void CCommand::SetEntity(World::CEntity::SharedPtr _pEntity)
    {
        m_pEntity = _pEntity;
    }

    World::CEntity::SharedPtr CCommand::GetEntity() const
    {
        return m_pEntity;
    }

    void CCommand::SetMovingDirection(EDirection _Direction)
    {
        m_MovingDirection = _Direction;
    }

    CCommand::EDirection CCommand::GetMovingDirection() const
    {
        return m_MovingDirection;
    }
} // namespace Logic

