#include "world/world_meta_entity.h"

namespace World
{
    CMetaEntity::CMetaEntity(int _ID, EType _Type)
        : m_ID     (_ID)
        , m_Type   (_Type)
        , m_Facets ()
        , m_pNext  (nullptr)
    {
    }
} // namespace World