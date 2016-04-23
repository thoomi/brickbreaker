#pragma once

#include "core/core_aabb3.h"
#include "core/core_vector3.h"

#include "world/world_meta_entity.h"

namespace World
{
    class CEntityFolder;
} 

namespace World
{
	class CEntity
	{
        public:

            typedef std::shared_ptr<CEntity> SharedPtr;
            typedef std::weak_ptr<CEntity>   WeakPtr;

        public:

            CFacetContainer<CMetaEntity> m_Facets; ///< Facet containter with data of the other modules

        public:

            Core::CVector3 GetPosition() const;
            void SetPosition(const Core::CVector3& _rPosition);

            const Core::CAABB3& GetAABB() const;

            const CMetaEntity& GetMetaEntity() const;

        public:

            CEntity();

		private:

			CEntity(const CEntity& _rEntity);
			CEntity& operator = (const CEntity& _rVector);

		private:

			int                    m_ID;	    ///< Unique ID for the entity
			bool                   m_IsDynamic; ///< Determine wheter the entity can move or not
			Core::CVector3         m_Position;  ///< The entity's position on the map
			Core::CAABB3           m_AABB;      ///< Axis aligned bounding box of the entity
			CMetaEntity::SharedPtr m_pMeta;     ///< Global entity data shared by all entities of this type

		private:
			
			CEntityFolder* m_pFolder;   ///< Corresponding folder which contains the entity
			SharedPtr      m_pNext;     ///< Next entity in the folder (intrusive list connection)
			WeakPtr        m_pPrevious; ///< Previous entity in the folder (intrusive list connection)

		private:

			friend CMap;
	};
} // namespace World