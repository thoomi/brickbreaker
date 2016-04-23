#pragma once

#include "gui/gui_element.h"

#include <vector>

namespace Gfx
{
    class CGuiRenderer
    {
        public:

            typedef std::vector<Gui::CElement::SharedPtr> GuiElementContainer;

        public:

            static CGuiRenderer& GetInstance();
            
        public:

            void RegisterGuiElement(Gui::CElement::SharedPtr _pElement);
            void UnregisterGuiElement(int _ID);

        public:

            void Render();

        private:

            CGuiRenderer();
            ~CGuiRenderer();

        private:

            GuiElementContainer m_GuiElements;
    };
} // namespace Gfx