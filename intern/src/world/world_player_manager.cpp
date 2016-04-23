#include "world/world_player_manager.h"

#include <assert.h>

namespace World
{
    CPlayerManager& CPlayerManager::GetInstance()
    {
        static CPlayerManager s_Instance;

        return s_Instance;
    }

    CPlayerManager::CPlayerManager()
        : m_Players()
    {
    }

    CPlayer::SharedPtr CPlayerManager::CreatePlayer(EPlayerID _ID)
    {
        assert(_ID >= 0 && _ID < MaxNumberOfPlayers);

        CPlayer::SharedPtr pPlayer = std::make_shared<CPlayer>(_ID);

        m_Players[_ID] = pPlayer;

        return pPlayer;
    }

    void CPlayerManager::DeletePlayer(EPlayerID _ID)
    {
        assert(_ID >= 0 && _ID < MaxNumberOfPlayers);

        m_Players[_ID] = nullptr;
    }

    CPlayer::SharedPtr CPlayerManager::GetPlayer(EPlayerID _ID)
    {
        assert(_ID >= 0 && _ID < MaxNumberOfPlayers);

        return m_Players[_ID];
    }
} // namespace World