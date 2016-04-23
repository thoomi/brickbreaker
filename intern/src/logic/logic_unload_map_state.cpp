#include "logic/logic_unload_map_state.h"

#include "world/world_map.h"
#include "world/world_player_manager.h"

namespace Logic
{
    CUnloadMapState& CUnloadMapState::GetInstance()
    {
        static CUnloadMapState s_Instance;

        return s_Instance;
    }

    CUnloadMapState::CUnloadMapState()
    {
    }

    CUnloadMapState::~CUnloadMapState()
    {
    }

    void CUnloadMapState::OnEnter()
    {

    }

    int CUnloadMapState::OnRun()
    {
        World::CMap& Map = World::CMap::GetInstance();

        // -----------------------------------------------------------------------------
        // Remove all entities from the map.
        // -----------------------------------------------------------------------------
        Map.Finalize();

        // -----------------------------------------------------------------------------
        // Remove player.
        // -----------------------------------------------------------------------------
        World::CPlayerManager::GetInstance().DeletePlayer(World::CPlayerManager::Player1);


        return 1;
    }

    void CUnloadMapState::OnLeave()
    {

    }
} // namespace Logic

