#pragma once

#include "world/world_entity.h"
#include "world/world_meta_entity.h"

namespace World
{
    class CRegion;
}

namespace World
{
	class CEntityFolder
	{
        public:

            CEntityFolder();

        private:

            CEntityFolder(const CEntityFolder& _rEntity);
            CEntityFolder& operator = (const CEntityFolder& _rVector);

        private:

            CMetaEntity::EType m_Type;      ///< Category of the entities in this folder
            CEntity::SharedPtr m_pEntities; ///< Start point of the intrusive list of all entities within this folder
            CRegion*           m_pRegion;   ///< Corresponding region
	
        private:

            friend CMap;
    };
} // namespace World