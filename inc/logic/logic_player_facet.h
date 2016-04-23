#pragma once

#include "core/core_vector3.h"

#include "world/world_entity.h"

#include <memory>

namespace Logic
{
    class CPlayerFacet
    {
        public:

            typedef std::shared_ptr<CPlayerFacet> SharedPtr;
            typedef std::unique_ptr<CPlayerFacet> UniquePtr;

        public:

            bool                      m_IsBallReleased;
            World::CEntity::SharedPtr m_AttachedBall;
            Core::CVector3            m_Velocity;
    };
} // namespace Logic