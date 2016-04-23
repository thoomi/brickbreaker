#include "world/world_entity.h"

namespace World
{    
    CEntity::CEntity()
        : m_Facets    ()
		, m_ID        (0)
		, m_IsDynamic (false)
		, m_Position  ()
		, m_AABB      ()
		, m_pMeta     (nullptr)
		, m_pFolder   (nullptr)
		, m_pNext     (nullptr)
        , m_pPrevious ()
	{
	}

    Core::CVector3 CEntity::GetPosition() const
    {
        return m_Position;
    }

    void CEntity::SetPosition(const Core::CVector3& _rPosition)
    {
        Core::CVector3 Offset = _rPosition - m_Position;

        m_AABB.m_Min += Offset;
        m_AABB.m_Max += Offset;

        m_Position = _rPosition;
    }


    const Core::CAABB3& CEntity::GetAABB() const
    {
        return m_AABB;
    }

    const CMetaEntity& CEntity::GetMetaEntity() const
    {
        return *m_pMeta;
    }

} // namespace World