#pragma once

#include <memory>

namespace Gfx
{
    class CConsoleFacet
    {
        public:

            typedef std::shared_ptr<CConsoleFacet> SharedPtr;
            typedef std::unique_ptr<CConsoleFacet> UniquePtr;

        public:

            char m_Symbol;
            char m_StartSymbol;
            char m_EndSymbol;

            unsigned short m_MainColor;
            unsigned short m_BorderColor;
    };
} // namespace Gfx