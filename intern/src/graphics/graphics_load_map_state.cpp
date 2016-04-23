#include "graphics/graphics_console.h"
#include "graphics/graphics_console_facet.h"
#include "graphics/graphics_load_map_state.h"

#include "world/world_map.h"

#include <assert.h>

namespace Gfx
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

        // -----------------------------------------------------------------------------
        // Setup the gfx meta entities, assuming that their corresponding world meta 
        // entity already exists with the given type and id.
        // -----------------------------------------------------------------------------
        auto pGfxPlayerFacet = std::make_shared<CConsoleFacet>();

        pGfxPlayerFacet->m_MainColor   = CConsole::RedOnRed;
        pGfxPlayerFacet->m_BorderColor = CConsole::RedOnRed;
        pGfxPlayerFacet->m_Symbol      = '-';
        pGfxPlayerFacet->m_EndSymbol   = '~';
        pGfxPlayerFacet->m_StartSymbol = '~';

        auto pPlayerMetaEntity = Map.GetMetaEntity(World::CMetaEntity::Player, 1);

        assert(pPlayerMetaEntity != nullptr);

        pPlayerMetaEntity->m_Facets.SetFacet(World::CMetaEntity::Gfx, pGfxPlayerFacet);



        auto pGfxBallFacet = std::make_shared<CConsoleFacet>();

        pGfxBallFacet->m_MainColor   = CConsole::YellowOnYellow;
        pGfxBallFacet->m_BorderColor = CConsole::YellowOnBlack;
        pGfxBallFacet->m_Symbol      = 'O';
        pGfxBallFacet->m_EndSymbol   = ')';
        pGfxBallFacet->m_StartSymbol = '(';

        auto pBallMetaEntity = Map.GetMetaEntity(World::CMetaEntity::Ball, 1);

        assert(pBallMetaEntity != nullptr);

        pBallMetaEntity->m_Facets.SetFacet(World::CMetaEntity::Gfx, pGfxBallFacet);



        auto pGfxBrickFacet = std::make_shared<CConsoleFacet>();

        pGfxBrickFacet->m_MainColor   = CConsole::CyanOnCyan;
        pGfxBrickFacet->m_BorderColor = CConsole::ForegroundGreen;
        pGfxBrickFacet->m_Symbol      = '#';
        pGfxBrickFacet->m_EndSymbol   = ':';
        pGfxBrickFacet->m_StartSymbol = ':';

        auto pBrickMetaEntity = Map.GetMetaEntity(World::CMetaEntity::Brick, 1);

        assert(pBrickMetaEntity != nullptr);

        pBrickMetaEntity->m_Facets.SetFacet(World::CMetaEntity::Gfx, pGfxBrickFacet);

        return 1;
    }

    void CLoadMapState::OnLeave()
    {

    }
} // namespace Gfx