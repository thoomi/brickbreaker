#include "core/core_algorithm.h"
#include "core/core_random.h"

#include "logic/logic_ball_facet.h"
#include "logic/logic_command_queue.h"
#include "logic/logic_play_state.h"
#include "logic/logic_player_facet.h"

#include "world/world_map.h"
#include "world/world_player_manager.h"

namespace Logic
{
    CPlayState& CPlayState::GetInstance()
    {
        static CPlayState s_Instance;

        return s_Instance;
    }

    CPlayState::CPlayState()
    {
    }

    CPlayState::~CPlayState()
    {
    }

    void CPlayState::OnEnter()
    {
            
    }

    int CPlayState::OnRun(float _ElapsedTime)
    {
        // -----------------------------------------------------------------------------
        // Process queued commands.
        // -----------------------------------------------------------------------------
        auto& CommandQueue = CCommandQueue::GetInstance();

        while (CommandQueue.HasCommand())
        {
            auto rCommand = CommandQueue.GetNextCommand();

            switch (rCommand.GetType())
            {
                case CCommand::MoveEntity:
                {
                    ProcessMoveCommand(rCommand);
                    break;
                }
                   
                case CCommand::StandardAction:
                {
                    ProcessActionCommand(rCommand);
                    break;
                }
                    
                default:
                    break;
            }

            CommandQueue.PopCommand();
        }

        // -----------------------------------------------------------------------------
        // Calculate new player position.
        // -----------------------------------------------------------------------------
        World::CMap& Map = World::CMap::GetInstance();

        auto pPlayer       = World::CPlayerManager::GetInstance().GetPlayer(World::CPlayerManager::Player1);
        auto pPlayerEntity = pPlayer->GetEntity();
        auto pPlayerFacet  = pPlayerEntity->m_Facets.GetFacet<CPlayerFacet>(World::CMetaEntity::Logic);
        
        Core::CVector3 NewPlayerPosition = pPlayerEntity->GetPosition() + pPlayerFacet->m_Velocity * _ElapsedTime;

        float LeftWorldBound = (pPlayerEntity->GetAABB().m_Max[Core::CVector3::X] - pPlayerEntity->GetAABB().m_Min[Core::CVector3::X]) / 2.0f;
        float RightWorldBound = World::CMap::s_MaxNumberOfMetersX - LeftWorldBound;

        NewPlayerPosition[Core::CVector3::X] = Algo::Clamp<float>(NewPlayerPosition[Core::CVector3::X], LeftWorldBound, RightWorldBound);

        Map.MoveEntity(*pPlayerEntity, NewPlayerPosition);


        // -----------------------------------------------------------------------------
        // Calculate new ball position.
        // -----------------------------------------------------------------------------
        auto pBallEntity = pPlayerFacet->m_AttachedBall;
        auto pBallFacet  = pBallEntity->m_Facets.GetFacet<CBallFacet>(World::CMetaEntity::Logic);

        Core::CVector3 NewBallPosition = pBallEntity->GetAABB().GetCenter();
        

        // -----------------------------------------------------------------------------
        // Keep ball in world bounds
        // -----------------------------------------------------------------------------
        if (NewBallPosition[0] < pBallEntity->GetAABB().GetExtentX())
        {
            pBallFacet->m_Velocity[0] *= -1.0f;
        }
        else if (NewBallPosition[0] > (World::CMap::s_MaxNumberOfMetersX - pBallEntity->GetAABB().GetExtentX()))
        {
            pBallFacet->m_Velocity[0] *= -1.0f;
        }

        if (NewBallPosition[1] < pBallEntity->GetAABB().GetExtentY() * 2.0f)
        {
            pBallFacet->m_Velocity[1] *= -1.0f;
        }
        else if (NewBallPosition[1] > (World::CMap::s_MaxNumberOfMetersY - pBallEntity->GetAABB().GetExtentY() * 2.0f))
        {
            pBallFacet->m_Velocity[0] = 0.0f;
            pBallFacet->m_Velocity[1] = 0.0f;
            pBallFacet->m_Velocity[2] = 0.0f;

            NewBallPosition[0] = pPlayerEntity->GetPosition()[0];
            NewBallPosition[1] = pPlayerEntity->GetPosition()[1] - 2.0f;
            NewBallPosition[2] = 0.0f;

            pPlayerFacet->m_IsBallReleased = false;
            pPlayer->ClearBrickCount();
        }

        // -----------------------------------------------------------------------------
        // Check for any collisions
        // -----------------------------------------------------------------------------
        Core::CVector3 Delta = pBallFacet->m_Velocity * _ElapsedTime;

        Core::CAABB3::CollisionInfo CollisionInfo;
        
        if (!pPlayerFacet->m_IsBallReleased)
        {
            NewBallPosition[0] = NewPlayerPosition[0];
        }
        else
        {
            // -----------------------------------------------------------------------------
            // Check for ball with player collision.
            // -----------------------------------------------------------------------------
            CollisionInfo = pPlayerEntity->GetAABB().GetCollisionInfo(pBallEntity->GetAABB(), Delta);

            if (CollisionInfo.m_Time < 1.0f)
            {
                // -----------------------------------------------------------------------------
                // Ball collided with player --> Invert vertical velocity and determine the 
                // horizontal velocity based on the sign and delta of the X-Axis vectors.
                // -----------------------------------------------------------------------------
                pBallFacet->m_Velocity[1] *= -1.0f;
                pBallFacet->m_Velocity[0] = (pBallEntity->GetPosition()[0] - pPlayerEntity->GetPosition()[0]) * 3.0f;
            }
            else
            {
                // ---------------------- -------------------------------------------------------
                // Check for any collisions with bricks.
                // -----------------------------------------------------------------------------
                auto EntityIteratorEnd = Map.EntitiesEnd();
                World::CEntity* pDoomedBrick = nullptr;

                for (auto EntityIterator = Map.EntitiesBegin(); EntityIterator != EntityIteratorEnd; EntityIterator.Next())
                {
                    if (EntityIterator->GetMetaEntity().m_Type == World::CMetaEntity::Brick)
                    {
                        Core::CAABB3::CollisionInfo CurrentInfo = EntityIterator->GetAABB().GetCollisionInfo(pBallEntity->GetAABB(), Delta);

                        if (CurrentInfo.m_Time < 1.0f)
                        {
                            if (CurrentInfo.m_Time < CollisionInfo.m_Time)
                            {
                                CollisionInfo.m_Time = CurrentInfo.m_Time;
                                pDoomedBrick = &*EntityIterator;
                            }
                        }
                    }
                }

                if (pDoomedBrick != nullptr)
                {
                    Map.RemoveEntity(*pDoomedBrick);

                    pPlayer->CountDestroyedBrick();

                    // -----------------------------------------------------------------------------
                    // Deflecting on x-Axis
                    // -----------------------------------------------------------------------------
                    float Dot = pBallFacet->m_Velocity[0] * CollisionInfo.m_Normal[0] + pBallFacet->m_Velocity[1] * CollisionInfo.m_Normal[1];

                    float UX = CollisionInfo.m_Normal[0] * Dot;
                    float WX = pBallFacet->m_Velocity[0] - UX;

                    pBallFacet->m_Velocity[0] = WX - UX;
                    pBallFacet->m_Velocity[1] *= -1.0f;
                }
            }
        }


        NewBallPosition += Delta * CollisionInfo.m_Time;

        NewBallPosition[0] = Algo::Clamp(NewBallPosition[0], 0.0f, static_cast<float>(World::CMap::s_MaxNumberOfMetersX - 0.5f));
        NewBallPosition[1] = Algo::Clamp(NewBallPosition[1], 0.0f, static_cast<float>(World::CMap::s_MaxNumberOfMetersY - 0.5f));

        Map.MoveEntity(*pBallEntity, NewBallPosition);

        return 0;
    }

    void CPlayState::OnLeave()
    {
            
    }

    void CPlayState::ProcessMoveCommand(const CCommand& _rCommand)
    {
        auto pEntity = _rCommand.GetEntity();

        if (pEntity->GetMetaEntity().m_Type == World::CMetaEntity::Player)
        {
            auto pFacet = pEntity->m_Facets.GetFacet<CPlayerFacet>(World::CMetaEntity::Logic);

            switch (_rCommand.GetMovingDirection())
            {
                case CCommand::Stop:
                    pFacet->m_Velocity = Core::CVector3(0.0f, 0.0f, 0.0f);
                    break;

                case CCommand::Left:
                    pFacet->m_Velocity = Core::CVector3(-20.0f, 0.0f, 0.0f);
                    break;

                case CCommand::Right:
                    pFacet->m_Velocity = Core::CVector3(20.0f, 0.0f, 0.0f);
                    break;

                default:
                    break;
            }
        }
    }

    void CPlayState::ProcessActionCommand(const CCommand& _rCommand)
    {
        auto pEntity = _rCommand.GetEntity();

        if (pEntity->GetMetaEntity().m_Type == World::CMetaEntity::Player)
        {
            auto pPlayerFacet = pEntity->m_Facets.GetFacet<CPlayerFacet>(World::CMetaEntity::Logic);

            if (!pPlayerFacet->m_IsBallReleased)
            {
                auto pBallFacet = pPlayerFacet->m_AttachedBall->m_Facets.GetFacet<CBallFacet>(World::CMetaEntity::Logic);


                float Random = Core::Random::GetRandomFloat(2.0f, 10.0f) * Core::Random::GetRandomFloatSign();

                pBallFacet->m_Velocity = Core::CVector3(Random, -15.0f, 0.0f);

                pPlayerFacet->m_IsBallReleased = true;
            }
        }
    }
} // namespace Logic

