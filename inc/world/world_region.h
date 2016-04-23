#pragma once

#include "core/core_aabb3.h"

#include "world/world_entity_folder.h"
#include "world/world_meta_entity.h"

namespace World
{
	class CRegion
	{
        public:

            static const int s_NumberOfMetersX = 8;
            static const int s_NumberOfMetersY = 6;

        private:

            CRegion();
            CRegion(const CRegion& _rRegion);
            CRegion& operator = (const CRegion& _rRegion);

        private:

            int          m_ID;
            Core::CAABB3 m_DefaultAABB;
            Core::CAABB3 m_StaticEntityAABB;
            Core::CAABB3 m_DynamicEntityAABB;

        private:

            CEntityFolder m_pEntityFolders[CMetaEntity::EType::NumberOfTypes];

        private:

            friend CMap;
	};
} // namespace World