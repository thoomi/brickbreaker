#include "core/core_algorithm.h"

#include "graphics/graphics_console.h"
#include "graphics/graphics_console_facet.h"
#include "graphics/graphics_entity_renderer.h"

#include "world/world_map.h"

namespace Gfx
{
    CEntityRenderer& CEntityRenderer::GetInstance()
    {
        static CEntityRenderer s_Instance;

        return s_Instance;
    }

    CEntityRenderer::CEntityRenderer()
    {
    }

    CEntityRenderer::~CEntityRenderer()
    {
            
    }

    void CEntityRenderer::Render()
    {
        auto& Console = CConsole::GetInstance();

        World::CMap& Map = World::CMap::GetInstance();

        auto EntityIteratorEnd = Map.EntitiesEnd();
            
        int GuiOffset = 3;


        for (auto EntityIterator = Map.EntitiesBegin(); EntityIterator != EntityIteratorEnd; EntityIterator.Next())
        {
            World::CEntity&     rEntity = *EntityIterator;
            const Core::CAABB3& rAABB = rEntity.GetAABB();
            auto pEntityFacet = rEntity.GetMetaEntity().m_Facets.GetFacet<CConsoleFacet>(World::CMetaEntity::Gfx);


            int MinX = Algo::Max<int>(0, static_cast<int>(rAABB.m_Min[Core::CVector3::X]));
            int MaxX = Algo::Max<int>(0, static_cast<int>(rAABB.m_Max[Core::CVector3::X]));
            int MinY = Algo::Max<int>(0, static_cast<int>(rAABB.m_Min[Core::CVector3::Y]));
            int MaxY = Algo::Max<int>(0, static_cast<int>(rAABB.m_Max[Core::CVector3::Y]));

            for (int IndexOfRow = MinY; IndexOfRow < MaxY; ++IndexOfRow)
            {
                for (int IndexOfColumn = MinX; IndexOfColumn < MaxX; ++IndexOfColumn)
                {
                    if (IndexOfColumn == MinX)
                    {
                        Console.SetPrintAttribute(pEntityFacet->m_BorderColor);
                        Console.Print(pEntityFacet->m_StartSymbol, IndexOfColumn, IndexOfRow + GuiOffset);
                    }
                    else if (IndexOfColumn == MaxX - 1)
                    {
                        Console.SetPrintAttribute(pEntityFacet->m_BorderColor);
                        Console.Print(pEntityFacet->m_EndSymbol, IndexOfColumn, IndexOfRow + GuiOffset);
                    }
                    else
                    {
                        Console.SetPrintAttribute(pEntityFacet->m_MainColor);
                        Console.Print(pEntityFacet->m_Symbol, IndexOfColumn, IndexOfRow + GuiOffset);
                    }
                }
            }
        }
    }
} // namespace Gfx

