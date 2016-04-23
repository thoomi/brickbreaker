#include "logic/logic_ball_facet.h"
#include "logic/logic_load_map_state.h"
#include "logic/logic_player_facet.h"

#include "world/world_map.h"
#include "world/world_player_manager.h"

namespace Logic
{
    CLoadMapState& CLoadMapState::GetInstance()
    {
        static CLoadMapState s_Instance;

        return s_Instance;
    }

    CLoadMapState::CLoadMapState()
    {
    }

    CLoadMapState::~CLoadMapState()
    {
    }

    void CLoadMapState::OnEnter()
    {

    }

    int CLoadMapState::OnRun()
    {
        World::CMap& Map = World::CMap::GetInstance();

        Map.Initialize();

        // -----------------------------------------------------------------------------
        // Initialize bricks.
        // -----------------------------------------------------------------------------
        int NumberOfBricksPerRow    = 10;
        int NumberOfBricksPerColumn = 8;

        float BrickWidth      = static_cast<float>( World::CMap::s_MaxNumberOfMetersX / NumberOfBricksPerRow);
        float BrickHeight     = static_cast<float>((World::CMap::s_MaxNumberOfMetersY / 2) / NumberOfBricksPerColumn);
        float HalfBrickWidth  = BrickWidth / 2.0f;
        float HalfBrickHeight = BrickHeight / 2.0f;

        for (int IndexOfRow = 0; IndexOfRow < NumberOfBricksPerColumn; IndexOfRow++)
        {
            for (int IndexOfColumn = 0; IndexOfColumn < NumberOfBricksPerRow; IndexOfColumn++)
            {
                Core::CVector3 Position = Core::CVector3(BrickWidth * IndexOfColumn + HalfBrickWidth, BrickHeight * IndexOfRow + HalfBrickHeight, 0.0f);
                Core::CAABB3   AABB     = Core::CAABB3(Position, BrickWidth, BrickHeight, 1.0f);

                Map.AddEntity(Map.CreateEntity(World::CMetaEntity::EType::Brick, 1, false, Position, AABB));
            }
        }

        // -----------------------------------------------------------------------------
        // Initialize player.
        // -----------------------------------------------------------------------------
        float PlayerWidth     = 10.0f;
        float PlayerHeight    = 1.0f;
        float PlayerPositionX = (World::CMap::s_MaxNumberOfMetersX / 2.0f);
        float PlayerPositionY = World::CMap::s_MaxNumberOfMetersY - PlayerHeight;

        Core::CVector3 PlayerPosition = Core::CVector3(PlayerPositionX, PlayerPositionY, 0.0f);
        Core::CAABB3   PlayerAABB     = Core::CAABB3(PlayerPosition, PlayerWidth, PlayerHeight, 1.0f);

        World::CEntity::SharedPtr pPlayerEntity     = Map.CreateEntity(World::CMetaEntity::EType::Player, 1, true, PlayerPosition, PlayerAABB);
        CPlayerFacet::SharedPtr   pPlayerLogicFacet = std::make_shared<CPlayerFacet>();

        pPlayerEntity->m_Facets.SetFacet(World::CMetaEntity::Logic, pPlayerLogicFacet);

        Map.AddEntity(pPlayerEntity);


        World::CPlayer::SharedPtr pPlayer = World::CPlayerManager::GetInstance().CreatePlayer(World::CPlayerManager::Player1);

        pPlayer->SetPlayerName("Mr. Pink");
        pPlayer->SetEntity(pPlayerEntity);


        // -----------------------------------------------------------------------------
        // Initialize ball.
        // -----------------------------------------------------------------------------
        float BallWidth  = 2.0f;
        float BallHeight = 1.0f;

        float BallPositionX = PlayerPosition[Core::CVector3::X];
        float BallPositionY = PlayerPosition[Core::CVector3::Y] - 2.0f;

        Core::CVector3 BallPosition = Core::CVector3(BallPositionX, BallPositionY, 0.0f);
        Core::CAABB3   BallAABB     = Core::CAABB3(BallPosition, BallWidth, BallHeight, 1.0f);

        World::CEntity::SharedPtr pBallEntity     = Map.CreateEntity(World::CMetaEntity::EType::Ball, 1, true, BallPosition, BallAABB);
        CBallFacet::SharedPtr     pBallLogicFacet = std::make_shared<CBallFacet>();

        pBallLogicFacet->m_OwnerID = pPlayer->GetID();

        pBallEntity->m_Facets.SetFacet(World::CMetaEntity::Logic, pBallLogicFacet);

        Map.AddEntity(pBallEntity);


        // -----------------------------------------------------------------------------
        // Connect ball initially to player.
        // -----------------------------------------------------------------------------
        pPlayerLogicFacet->m_AttachedBall   = pBallEntity;
        pPlayerLogicFacet->m_IsBallReleased = false;

        return 1;
    }

    void CLoadMapState::OnLeave()
    {

    }
} // namespace Logic

