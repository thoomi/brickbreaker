#pragma once

#include "gui/gui_element.h"

#include <memory>

namespace Gui
{
    class CGuiNumber : public CElement
    {
        public:
            
            typedef std::shared_ptr<CGuiNumber> SharedPtr;
            typedef std::unique_ptr<CGuiNumber> UniquePtr;

        public:

            CGuiNumber(int _ID);
            ~CGuiNumber(void);

        public:

            void SetNumber(int _Number);
            void SetMinLength(int _Length);

        private:

            int m_MinLength;
    };
} // namespace Gui