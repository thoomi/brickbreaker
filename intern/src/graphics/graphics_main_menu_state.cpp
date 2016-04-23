#include "graphics/graphics_main_menu_state.h"
#include "graphics/graphics_console.h"
#include "graphics/graphics_gui_renderer.h"

namespace Gfx
{
    CMainMenuState& CMainMenuState::GetInstance()
    {
        static CMainMenuState s_Instance;

        return s_Instance;
    }

    CMainMenuState::CMainMenuState()
    {
    }

    CMainMenuState::~CMainMenuState()
    {
    }

    void CMainMenuState::OnEnter()
    {

    }

    int CMainMenuState::OnRun()
    {
        auto& Console = CConsole::GetInstance();

        Console.Clear();

        CGuiRenderer::GetInstance().Render();

        Console.ActivateBuffer();
        Console.SwapBuffers();

        return 1;
    }

    void CMainMenuState::OnLeave()
    {

    }
} // namespace Gfx