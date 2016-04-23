#include "graphics/graphics_console.h"
#include "graphics/graphics_entity_renderer.h"
#include "graphics/graphics_gui_renderer.h"
#include "graphics/graphics_play_state.h"

namespace Gfx
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

    int CPlayState::OnRun()
    {
        auto& Console = CConsole::GetInstance();

        Console.Clear();


        CEntityRenderer::GetInstance().Render();
        CGuiRenderer::GetInstance().Render();


        Console.ActivateBuffer();
        Console.SwapBuffers();

        return 1;
    }

    void CPlayState::OnLeave()
    {

    }
} // namespace Gfx