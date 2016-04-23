#pragma once

#include "core/core_vector3.h"

#include <memory>

namespace Logic
{
    class CBallFacet
    {
        public:

            typedef std::shared_ptr<CBallFacet> SharedPtr;
            typedef std::unique_ptr<CBallFacet> UniquePtr;

        public:

            int            m_OwnerID;
            Core::CVector3 m_Velocity;
    };
} // namespace Logic