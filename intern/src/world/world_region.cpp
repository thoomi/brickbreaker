#include "world/world_region.h"

namespace World
{
    CRegion::CRegion()
        : m_ID                (-1)
        , m_DefaultAABB       ()
        , m_StaticEntityAABB  ()
        , m_DynamicEntityAABB ()
        , m_pEntityFolders    ()
    {
    }

} // namespace World