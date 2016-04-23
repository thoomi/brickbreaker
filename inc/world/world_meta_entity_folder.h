#pragma once

#include "world/world_meta_entity.h"

namespace World
{
    class CMetaEntityFolder
    {
        public:

            CMetaEntityFolder();
            ~CMetaEntityFolder();

        private:

            CMetaEntityFolder(const CMetaEntityFolder& _rMetaEntityFolder);
            CMetaEntityFolder& operator = (const CMetaEntityFolder& _rMetaEntityFolder);

        private:

            CMetaEntity::EType     m_Type;      ///< Category of the entities in this folder
            CMetaEntity::SharedPtr m_pEntities; ///< Start point of the intrusive list of all entities within this folder

        private:

            friend CMap;
    };
} // namespace World