#pragma once

#include "world/world_facet_container.h"

#include <memory>

namespace World
{
    class CMap;
}

namespace World
{
	class CMetaEntity
	{
        public:

            typedef std::shared_ptr<CMetaEntity> SharedPtr;

        public:

            enum EType
            {
                Player,
                Brick,
                Ball,
                NumberOfTypes,
                Undefined
            };

            enum EFacet
            {
                Gfx,
                Logic,
                NumberOfFacets
            };

        public:

            const int                    m_ID;
            const EType                  m_Type;
            CFacetContainer<CMetaEntity> m_Facets;

        public:

            CMetaEntity(int _ID, EType _Type);

        private:

            CMetaEntity(const CMetaEntity& _rMetaEntity);
            CMetaEntity& operator = (const CMetaEntity& _rMetaEntity);

        private:

            SharedPtr m_pNext; ///< Next meta entity in the folder (intrusive list)

        private:

            friend CMap;
	};
} // namespace World