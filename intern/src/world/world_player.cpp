#include "world/world_player.h"

namespace World
{
    CPlayer::CPlayer(int _ID)
        : m_ID(_ID)
        , m_PlayerName()
        , m_pEntity(nullptr)
        , m_NumberOfDestroyedBricks(0)
    {
    }

    int CPlayer::GetID() const
    {
        return m_ID;
    }

    void CPlayer::SetPlayerName(const std::string& _rName)
    {
        m_PlayerName = _rName;
    }

    const std::string& CPlayer::GetPlayerName() const
    {
        return m_PlayerName;
    }

    CEntity::SharedPtr CPlayer::GetEntity() const
    {
        return m_pEntity;
    }

    void CPlayer::SetEntity(CEntity::SharedPtr _pEntity)
    {
        m_pEntity = _pEntity;
    }

    int CPlayer::GetNumberOfDestroyedBricks()
    {
        return m_NumberOfDestroyedBricks;
    }

    void CPlayer::CountDestroyedBrick()
    {
        m_NumberOfDestroyedBricks++;
    }

    void CPlayer::ClearBrickCount()
    {
        m_NumberOfDestroyedBricks = 0;
    }

} // namespace World