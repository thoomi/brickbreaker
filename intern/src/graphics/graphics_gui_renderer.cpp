#include "graphics/graphics_console.h"
#include "graphics/graphics_gui_renderer.h"

namespace Gfx
{
    CGuiRenderer& CGuiRenderer::GetInstance()
    {
        static CGuiRenderer s_Instance;

        return s_Instance;
    }

    CGuiRenderer::CGuiRenderer()
        : m_GuiElements()
    {
    }

    CGuiRenderer::~CGuiRenderer()
    {
            
    }

    void CGuiRenderer::Render()
    {
        auto& Console = CConsole::GetInstance();

        for (auto& Element : m_GuiElements)
        {
            int StartPosX = Element->GetPositionX();
            int StartPosY = Element->GetPositionY();

            for (int IndexOfRow = 0; IndexOfRow < Element->GetHeight(); IndexOfRow++)
            {
                for (int IndexOfColumn = 0; IndexOfColumn < Element->GetWidth(); IndexOfColumn++)
                {
                    int LookupIndex    = IndexOfRow * Element->GetWidth() + IndexOfColumn;
                    char CurrentSymbol = Element->GetLayout().at(LookupIndex);

                    Console.SetPrintAttribute(Element->GetTextAttributeAt(LookupIndex));
                    Console.Print(CurrentSymbol, StartPosX + IndexOfColumn, StartPosY + IndexOfRow);
                }
            }
        }
    }

    void CGuiRenderer::RegisterGuiElement(Gui::CElement::SharedPtr _pElement)
    {
        m_GuiElements.push_back(_pElement);
    }

    void CGuiRenderer::UnregisterGuiElement(int _ID)
    {
        for (unsigned int IndexOfElement = 0; IndexOfElement < m_GuiElements.size(); IndexOfElement++)
        {
            if (m_GuiElements[IndexOfElement]->GetID() == _ID)
            {
                m_GuiElements.erase(m_GuiElements.begin() + IndexOfElement);
            }
        }
    }
} // namespace Gfx

