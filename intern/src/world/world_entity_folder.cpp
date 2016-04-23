#include "world/world_entity_folder.h"

namespace World
{
    CEntityFolder::CEntityFolder()
        : m_Type      (CMetaEntity::EType::Undefined)
        , m_pEntities (nullptr)
        , m_pRegion   (nullptr)
    {
    }

} // namespace World