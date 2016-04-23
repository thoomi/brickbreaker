#include "gui/gui_element_options_list.h"
#include "gui/gui_event_manager.h"
#include "gui/gui_main_menu_state.h"

#include "graphics/graphics_console.h"
#include "graphics/graphics_gui_renderer.h"

namespace Gui
{
    CMainMenuState& CMainMenuState::GetInstance()
    {
        static CMainMenuState s_Instance;

        return s_Instance;
    }

    CMainMenuState::CMainMenuState()
        : m_NextStateID(0)
        , m_OptionsList(nullptr)
    {
    }

    CMainMenuState::~CMainMenuState()
    {
    }

    void CMainMenuState::OnEnter()
    {
        CEventManager::GetInstance().RegisterListener(this);

        // -----------------------------------------------------------------------------
        // Setup some gui elements.
        // -----------------------------------------------------------------------------
        auto Logo = std::make_shared<CElement>(1);

        Logo->SetLayout(" ____       _      _    _                    _             "
                        "|  _ \\     (_)    | |  | |                  | |            "
                        "| |_) |_ __ _  ___| | _| |__  _ __ ___  __ _| | _____ _ __ "
                        "|  _ <| '__| |/ __| |/ / '_ \\| '__/ _ \\/ _` | |/ / _ \\ '__|"
                        "| |_) | |  | | (__|   <| |_) | | |  __/ (_| |   <  __/ |   "
                        "|____/|_|  |_|\\___|_|\\_\\_.__/|_|  \\___|\\__,_|_|\\_\\___|_|   ");

        Logo->SetHeight(6);
        Logo->SetWidth(59);
        Logo->SetPositionX(10);
        Logo->SetPositionY(16);

        Logo->SetBaseTextAttribute(Gfx::CConsole::YellowOnBlack);
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(Logo);


        
        auto HeadImage = std::make_shared<CElement>(2);

        HeadImage->SetLayout("              ________           "
                             "             /\\       \\          "
                             "            /  \\       \\         "
                             "           /    \\       \\        "
                             "          /      \\_______\\       "
                             "          \\      /       /       "
                             "        ___\\    /   ____/___     "
                             "       /\\   \\  /   /\\       \\    "
                             "      /  \\   \\/___/  \\       \\   "
                             "     /    \\       \\   \\       \\  "
                             "    /      \\_______\\   \\_______\\ "
                             "    \\      /       /   /       / "
                             "     \\    /       /   /       /  "
                             "      \\  /       /\\  /       /   "
                             "       \\/_______/  \\/_______/    ");
        
        HeadImage->SetHeight(15);
        HeadImage->SetWidth(33);
        HeadImage->SetPositionX(22);
        HeadImage->SetPositionY(0);

        HeadImage->SetBaseTextAttribute(Gfx::CConsole::CyanOnBlack);
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(HeadImage);
        


        auto Gras = std::make_shared<CElement>(3);
        Gras->SetLayout(" ____________________       "
                        "|                    |      "
                        "|                    |      "
                        "|                    |      "
                        "|                    |      "
                        "|                    |      "
                        "|                    |      "
                        "|                    |      "
                        "|____________________|      "
                        "          ||                "
                        "          ||                "
                        "          ||                "
                        "          ||   www          "
                        "   vwv    ||   )_(,;;;,     "
                        "   )_(    ||   \\|/ \\_/      "
                        "   \\|   \\ || /\\\\|/  |/      "
                        "___\\|//___||//_\\V/_\\|//__   ");

        Gras->SetHeight(17);
        Gras->SetWidth(28);
        Gras->SetPositionX(28);
        Gras->SetPositionY(23);

        Gras->SetBaseTextAttribute(Gfx::CConsole::GreenOnBlack);
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(Gras);


        auto Leprachaun = std::make_shared<CElement>(4);
        Leprachaun->SetLayout("         .-. "
                              "        ((`-)"
                              "         \\\\  "
                              "          \\\\ "
                              "   .=\"\"\"=._))"
                              "  /  .,   .' "
                              " /__(,_.-'   "
                              "`    /|      "
                              "    /_|__    "
                              "      | `))  "
                              "      |      "
                              "     -\"==    ");

        Leprachaun->SetHeight(12);
        Leprachaun->SetWidth(13);
        Leprachaun->SetPositionX(8);
        Leprachaun->SetPositionY(28);

        Leprachaun->SetBaseTextAttribute(Gfx::CConsole::PurpleOnBlack);
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(Leprachaun);


        auto MenuOptions = std::make_shared<COptionsList>(5);

        MenuOptions->SetPositionX(32);
        MenuOptions->SetPositionY(25);

        MenuOptions->AddItem("Play Game");
        MenuOptions->AddItem("Exit Game");
        MenuOptions->AddItem("Credits");

        m_OptionsList = MenuOptions;

        MenuOptions->SetBaseTextAttribute(Gfx::CConsole::RedOnBlack);
        Gfx::CGuiRenderer::GetInstance().RegisterGuiElement(MenuOptions);
        CEventManager::GetInstance().RegisterListener(m_OptionsList.get());


        m_NextStateID = 0;
    }

    int CMainMenuState::OnRun()
    {
        return m_NextStateID;
    }

    void CMainMenuState::OnLeave()
    {
        CEventManager::GetInstance().UnregisterListener(this);
        CEventManager::GetInstance().UnregisterListener(m_OptionsList.get());

        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(1);
        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(2);
        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(3);
        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(4);
        Gfx::CGuiRenderer::GetInstance().UnregisterGuiElement(5);

        m_OptionsList.reset();
    }


    void CMainMenuState::OnEvent(const Core::CUserEvent& _rEvent)
    {
        if (_rEvent.GetType() == Core::CUserEvent::Input)
        {
            if (_rEvent.GetAction() == Core::CUserEvent::KeyPressed)
            {
                switch (_rEvent.GetKey())
                {
                    case Core::CUserEvent::KeyReturn:
                    {
                        switch(m_OptionsList->GetCurrentItem())
                        {
                            case 0:
                                m_NextStateID = 3;
                                break;
                            case 1:
                                m_NextStateID = 6;
                                break;
                        }

                        break;
                    }

                    case Core::CUserEvent::KeyEscape:
                    {
                        m_NextStateID = 6;
                        break;
                    }
                        
                    default:
                        break;
                }
            }
        }
    }
} // namespace Gui