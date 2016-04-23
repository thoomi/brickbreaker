#include "world\world_meta_entity_folder.h"

namespace World
{
    CMetaEntityFolder::CMetaEntityFolder()
        : m_Type      (CMetaEntity::EType::Undefined)
        , m_pEntities (nullptr)
    {
    }

    CMetaEntityFolder::~CMetaEntityFolder()
    {   
    }

} // namespace World