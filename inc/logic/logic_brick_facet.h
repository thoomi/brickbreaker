#pragma once

#include <memory>

namespace Logic
{
    class CBrickFacet
    {
        public:

            typedef std::shared_ptr<CBrickFacet> SharedPtr;
            typedef std::unique_ptr<CBrickFacet> UniquePtr;

    };
} // namespace Logic