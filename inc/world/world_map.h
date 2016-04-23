#pragma once

#include "world/world_region.h"
#include "world/world_meta_entity_folder.h"

namespace World
{
    class CEntityIterator
    {
        public:

            CEntityIterator(CEntity* _pEntity);

        public:

            CEntity& operator *  () const;
            CEntity* operator -> () const;

        public:

            CEntityIterator& Next();

        public:

            bool operator == (const CEntityIterator& _rOther);
            bool operator != (const CEntityIterator& _rOther); 

        private:

            CEntity* m_pCurrentEntity;
    };
}

namespace World
{
	class CMap
	{
        public:

            static const int s_NumberOfRegionsPerRow    = 10;
            static const int s_NumberOfRegionsPerColumn = 6;
            static const int s_MaxNumberOfRegions       = s_NumberOfRegionsPerRow    * s_NumberOfRegionsPerColumn;
            static const int s_MaxNumberOfMetersX       = s_NumberOfRegionsPerRow    * CRegion::s_NumberOfMetersX;
            static const int s_MaxNumberOfMetersY       = s_NumberOfRegionsPerColumn * CRegion::s_NumberOfMetersY;

        public:

            static CMap& GetInstance();

        public:

            void Initialize();
            void Finalize();

        public:

            CEntity::SharedPtr CreateEntity(CMetaEntity::EType _Type, int _MetaTypeID, bool _IsDynamic, const Core::CVector3& _rPosition, const Core::CAABB3& _rAABB);
            CEntity::SharedPtr RemoveEntity(CEntity& _rEntity);
            void MoveEntity(CEntity& _rEntity, const Core::CVector3& _rPosition);
            void AddEntity(CEntity::SharedPtr _pEntity);


        public:

            CMetaEntity::SharedPtr GetMetaEntity(CMetaEntity::EType _Type, int _ID) const;
            CMetaEntity::SharedPtr CreateMetaEntity(CMetaEntity::EType _Type, int _ID);

        public:

            CEntityIterator EntitiesBegin() const;
            CEntityIterator EntitiesEnd() const;

        public:

            CEntity* GetFirstEntity() const;
            CEntity* GetNextEntity(const CEntity* _pEntity) const;

        private:

            CRegion* GetRegion(const Core::CVector3& _rPosition);
            
        private:

            CRegion           m_pRegions[s_MaxNumberOfRegions];
            CMetaEntityFolder m_pMetaEntityFolders[CMetaEntity::EType::NumberOfTypes];

        private:

            CMap();
            CMap(const CMap& _rMap);
            CMap& operator = (const CMap& _rMap);
            ~CMap();


        private:

            enum
            {
                X,
                Y,
                Z
            };
	};
} // namespace World