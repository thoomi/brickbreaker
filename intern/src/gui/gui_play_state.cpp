#include "graphics/graphics_gui_renderer.h"
#include "graphics/graphics_console.h"

#include "gui/gui_element.h"
#include "gui/gui_element_number.h"
#include "gui/gui_event_manager.h"
#include "gui/gui_play_state.h"

#include "logic/logic_command.h"
#include "logic/logic_command_queue.h"

#include "world/world_player_manager.h"

namespace Gui
{
    CPlayState& CPlayState::GetInstance()
    {
        static CPlayState s_Instance;

        return s_Instance;
    }

    CPlayState::CPlayState()
        : m_MusicPlayer  ()
        , m_pBrickCounter(nullptr)
        , m_NextStateID  (0)
    {
    }

    CPlayState::~CPlayState()
    {
    }

    void CPlayState::OnEnter()
    {
        CEventManager::GetInstance().RegisterListener(this);

        m_MusicPlayer.SetSong(Core::Sound::CMusicPlayer::MissionImpossible);
        m_MusicPlayer.PlayInBackground();

        // -----------------------------------------------------------------------------
        // Setup some gui elements.
        // -----------------------------------------------------------------------------
        auto ScoreGuiElement = std::make_shared<CElement>(1);
        
        ScoreGuiElement->SetLayout("Score:");

        ScoreGuiElement->SetHeight(1);
        ScoreGuiElement->SetWidth(6);
        ScoreGuiElement->SetPositionX(59);
        ScoreGuiElement->SetPositionY(0);

        ScoreGuiElement->SetBaseTextAttribute(Gfx::CConsole::GreenOnBlack);
        
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(ScoreGuiElement);


        auto StatsNumber = std::make_shared<CGuiNumber>(2);

        StatsNumber->SetPositionX(67);
        StatsNumber->SetPositionY(0);

        StatsNumber->SetBaseTextAttribute(Gfx::CConsole::GreenOnBlack);
        StatsNumber->SetMinLength(3);
        StatsNumber->SetNumber(0);

        m_pBrickCounter = StatsNumber;
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(StatsNumber);


        auto SeparatorLine = std::make_shared<CElement>(3);

        SeparatorLine->SetLayout("================================================================================");
        SeparatorLine->SetBaseTextAttribute(Gfx::CConsole::CyanOnBlack);

        SeparatorLine->SetHeight(1);
        SeparatorLine->SetWidth(80);
        SeparatorLine->SetPositionX(0);
        SeparatorLine->SetPositionY(3);

        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(SeparatorLine);

        m_NextStateID = 0;
    }

    int CPlayState::OnRun()
    {
        // -----------------------------------------------------------------------------
        // Update stats counter UI element
        // -----------------------------------------------------------------------------
        auto pPlayer = World::CPlayerManager::GetInstance().GetPlayer(World::CPlayerManager::Player1);

        m_pBrickCounter->SetNumber(pPlayer->GetNumberOfDestroyedBricks());

        return m_NextStateID;
    }

    void CPlayState::OnLeave()
    {
        m_MusicPlayer.Stop();

        CEventManager::GetInstance().UnregisterListener(this);

        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(1);
        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(2);
        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(3);

        m_pBrickCounter.reset();
    }


    void CPlayState::OnEvent(const Core::CUserEvent& _rEvent)
    {
        // -----------------------------------------------------------------------------
        // Translate incoming user events into logical commands.
        // -----------------------------------------------------------------------------
        Logic::CCommand Command = Logic::CCommand();

        if (_rEvent.GetType() == Core::CUserEvent::Input)
        {
            if (_rEvent.GetAction() == Core::CUserEvent::KeyPressed)
            {
                switch (_rEvent.GetKey())
                {
                    case Core::CUserEvent::KeyLeft:
                        Command.SetType(Logic::CCommand::MoveEntity);
                        Command.SetMovingDirection(Logic::CCommand::EDirection::Left);
                        break;

                    case Core::CUserEvent::KeyRight:
                        Command.SetType(Logic::CCommand::MoveEntity);
                        Command.SetMovingDirection(Logic::CCommand::EDirection::Right);
                        break;

                    case Core::CUserEvent::KeySpace:
                        Command.SetType(Logic::CCommand::StandardAction);
                        break;

                    case Core::CUserEvent::KeyEscape:
                        // Next state id 5 for unload map state
                        m_NextStateID = 5;
                        break;

                    default:
                        break;
                }
            }
            else if (_rEvent.GetAction() == Core::CUserEvent::KeyReleased)
            {
                switch (_rEvent.GetKey())
                {
                    case Core::CUserEvent::KeyLeft:
                        Command.SetType(Logic::CCommand::MoveEntity);
                        Command.SetMovingDirection(Logic::CCommand::EDirection::Stop);
                        break;
                        
                    case Core::CUserEvent::KeyRight:
                        Command.SetType(Logic::CCommand::MoveEntity);
                        Command.SetMovingDirection(Logic::CCommand::EDirection::Stop);
                        break;

                    default:
                        break;
                }
            }
        }

        // -----------------------------------------------------------------------------
        // If we have got a valid command, get the corresponding player entity and attatch it.
        // -----------------------------------------------------------------------------
        if (Command.GetType() != Logic::CCommand::Undefined)
        {
            World::CEntity::SharedPtr pPlayerEntity = World::CPlayerManager::GetInstance().GetPlayer(World::CPlayerManager::Player1)->GetEntity();

            Command.SetEntity(pPlayerEntity);

            Logic::CCommandQueue::GetInstance().AddCommand(Command);
        }
    }
} // namespace Gui