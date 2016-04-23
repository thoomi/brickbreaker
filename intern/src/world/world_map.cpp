#include "world/world_map.h"

#include <assert.h>

namespace World
{
    CMap& CMap::GetInstance()
    {
        static CMap s_Singleton;

        return s_Singleton;
    }

    CMap::CMap()
        : m_pRegions()
    {
    }

    CMap::~CMap()
    {
        
    }

    CRegion* CMap::GetRegion(const Core::CVector3& _rPosition) 
    {
        int RegionX  = static_cast<int>(_rPosition[X] / CRegion::s_NumberOfMetersX);
        int RegionY  = static_cast<int>(_rPosition[Y] / CRegion::s_NumberOfMetersY);
        int RegionID = RegionX + RegionY * s_NumberOfRegionsPerRow;

        assert(RegionID < s_MaxNumberOfRegions);

        return &m_pRegions[RegionID];
    }

    void CMap::Initialize()
    {
        // -----------------------------------------------------------------------------
        // Initialize all regions and set the default parameters of the members.
        // -----------------------------------------------------------------------------
        for (int IndexOfRegion = 0; IndexOfRegion < s_MaxNumberOfRegions; IndexOfRegion++)
        {
            Core::CVector3 RegionPosition;

            RegionPosition[X] = static_cast<float>(IndexOfRegion % s_NumberOfRegionsPerColumn * CRegion::s_NumberOfMetersX);
            RegionPosition[Y] = static_cast<float>(IndexOfRegion / s_NumberOfRegionsPerRow    * CRegion::s_NumberOfMetersY);

            // -----------------------------------------------------------------------------
            // Initialize bounding boxes.
            // -----------------------------------------------------------------------------
            CRegion& rRegion = m_pRegions[IndexOfRegion];

            rRegion.m_ID = IndexOfRegion;

            rRegion.m_DefaultAABB.m_Min    = RegionPosition;
            rRegion.m_DefaultAABB.m_Max[X] = RegionPosition[X] + CRegion::s_NumberOfMetersX;
            rRegion.m_DefaultAABB.m_Max[Y] = RegionPosition[Y] + CRegion::s_NumberOfMetersY;

            rRegion.m_StaticEntityAABB  = rRegion.m_DefaultAABB;
            rRegion.m_DynamicEntityAABB = rRegion.m_DefaultAABB;

            // -----------------------------------------------------------------------------
            // Initialize static and dynamic entity folders for each type.
            // -----------------------------------------------------------------------------
            for (int IndexOfFolder = 0; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
            {
                rRegion.m_pEntityFolders[IndexOfFolder].m_pRegion = &rRegion;
                rRegion.m_pEntityFolders[IndexOfFolder].m_Type    = static_cast<CMetaEntity::EType>(IndexOfFolder);
            }
        }

        // -----------------------------------------------------------------------------
        // Initialize meta entity folders.
        // -----------------------------------------------------------------------------
        for (int IndexOfFolder = 0; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
        {
            m_pMetaEntityFolders[IndexOfFolder].m_Type = static_cast<CMetaEntity::EType>(IndexOfFolder);
        }
    }

    void CMap::Finalize()
    {
        // -----------------------------------------------------------------------------
        // Do Everything to cleanup the whole map.
        // -----------------------------------------------------------------------------
        for (int IndexOfRegion = 0; IndexOfRegion < s_MaxNumberOfRegions; IndexOfRegion++)
        {
            CRegion& rRegion = m_pRegions[IndexOfRegion];

            // -----------------------------------------------------------------------------
            // Clear static and dynamic entity folders for each type.
            // -----------------------------------------------------------------------------
            for (int IndexOfFolder = 0; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
            {
                rRegion.m_pEntityFolders[IndexOfFolder].m_pEntities = nullptr;
            }
        }


        for (int IndexOfFolder = 0; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
        {
            m_pMetaEntityFolders[IndexOfFolder].m_pEntities = nullptr;
        }
    }


    CEntity::SharedPtr CMap::CreateEntity(CMetaEntity::EType _Type, int _MetaTypeID, bool _IsDynamic, const Core::CVector3& _rPosition, const Core::CAABB3& _rAABB)
    {
        CEntity::SharedPtr     pEntity     = std::make_shared<CEntity>();
        CMetaEntity::SharedPtr pMetaEntity = GetMetaEntity(_Type, _MetaTypeID);

        if (pMetaEntity == nullptr)
        {
            pMetaEntity = CreateMetaEntity(_Type, _MetaTypeID);
        }

        // -----------------------------------------------------------------------------
        // Setup the entities attributes
        // -----------------------------------------------------------------------------
        pEntity->m_ID        = 0; // TODO: Implement a ID Generator / Manager
        pEntity->m_pMeta     = pMetaEntity;
        pEntity->m_IsDynamic = _IsDynamic;
        pEntity->m_Position  = _rPosition;
        pEntity->m_AABB      = _rAABB;

        return pEntity;
    }

    CEntity::SharedPtr CMap::RemoveEntity(CEntity& _rEntity)
    {
        assert(_rEntity.m_pFolder != nullptr);

        // -----------------------------------------------------------------------------
        // We can easily remove the entity because it holds its containing folder as
        // a member attribute.
        // -----------------------------------------------------------------------------
        CEntity::SharedPtr pDoomedEntity;

        if (CEntity::SharedPtr pPrevious = _rEntity.m_pPrevious.lock())
        {
            pDoomedEntity      = pPrevious->m_pNext;
            pPrevious->m_pNext = _rEntity.m_pNext;
        }
        else
        {
            pDoomedEntity = _rEntity.m_pFolder->m_pEntities;
            _rEntity.m_pFolder->m_pEntities = _rEntity.m_pNext;
        }

        if (_rEntity.m_pNext != nullptr)
        {
            _rEntity.m_pNext->m_pPrevious = _rEntity.m_pPrevious;
        }


        // -----------------------------------------------------------------------------
        // Not necessary but better for debugging :)
        // -----------------------------------------------------------------------------
        _rEntity.m_pFolder = nullptr;
        _rEntity.m_pNext   = nullptr;

        return pDoomedEntity;
    }

    void CMap::MoveEntity(CEntity& _rEntity, const Core::CVector3& _rPosition)
    {
        assert((_rEntity.m_pFolder != nullptr) && (_rEntity.m_pFolder->m_pRegion != nullptr));

        CRegion* pOldRegion = _rEntity.m_pFolder->m_pRegion;
        CRegion* pNewRegion = GetRegion(_rPosition);

        if (pOldRegion != pNewRegion)
        {
            CEntity::SharedPtr pEntity = RemoveEntity(_rEntity);

            pEntity->SetPosition(_rPosition);

            AddEntity(pEntity);
        }
        else
        {
            _rEntity.SetPosition(_rPosition);
        }
    }

    void CMap::AddEntity(CEntity::SharedPtr _pEntity)
    {
        // -----------------------------------------------------------------------------
        // Get Region and folder where to add the entity.
        // -----------------------------------------------------------------------------
        CRegion*       pMatchingRegion = GetRegion(_pEntity->m_Position);
        CEntityFolder* pMatchingFolder = &pMatchingRegion->m_pEntityFolders[_pEntity->m_pMeta->m_Type];

        assert(pMatchingFolder != nullptr);

        // -----------------------------------------------------------------------------
        // Push the entity to the front of the folder.
        // -----------------------------------------------------------------------------
        _pEntity->m_pFolder   = pMatchingFolder;
        _pEntity->m_pNext     = pMatchingFolder->m_pEntities;
        _pEntity->m_pPrevious.reset();

        if (pMatchingFolder->m_pEntities != nullptr)
        {
            pMatchingFolder->m_pEntities->m_pPrevious = _pEntity;
        }

        pMatchingFolder->m_pEntities = _pEntity;
    }

    CMetaEntity::SharedPtr CMap::GetMetaEntity(CMetaEntity::EType _Type, int _ID) const
    {
        CMetaEntity::SharedPtr pMetaEntity = m_pMetaEntityFolders[_Type].m_pEntities;

        while (pMetaEntity != nullptr)
        {
            if (pMetaEntity->m_ID == _ID)
            {
                return pMetaEntity;
            }

            pMetaEntity = pMetaEntity->m_pNext;
        }

        return nullptr;
    }

    CMetaEntity::SharedPtr CMap::CreateMetaEntity(CMetaEntity::EType _Type, int _ID)
    {
        CMetaEntity::SharedPtr pMetaEntity = std::make_shared<CMetaEntity>(_ID, _Type);

        CMetaEntityFolder& rMatchingFolder = m_pMetaEntityFolders[pMetaEntity->m_Type];
        
        pMetaEntity->m_pNext        = rMatchingFolder.m_pEntities;
        rMatchingFolder.m_pEntities = pMetaEntity;

        return pMetaEntity;
    }

    CEntityIterator CMap::EntitiesBegin() const
    {
        return CEntityIterator(GetFirstEntity());
    }

    CEntityIterator CMap::EntitiesEnd() const
    {
        return CEntityIterator(nullptr);
    }

    CEntity* CMap::GetFirstEntity() const
    {
        // -----------------------------------------------------------------------------
        // Find the first non empty entity folder.
        // -----------------------------------------------------------------------------
        for (int IndexOfRegion = 0; IndexOfRegion < s_MaxNumberOfRegions; IndexOfRegion++)
        {
            for (int IndexOfFolder = 0; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
            {
                const CEntityFolder& rFolder = m_pRegions[IndexOfRegion].m_pEntityFolders[IndexOfFolder];

                if (rFolder.m_pEntities != nullptr)
                {
                    return rFolder.m_pEntities.get();
                }
            }
        }

        return nullptr;
    }

    CEntity* CMap::GetNextEntity(const CEntity* _pEntity) const
    {
        assert(_pEntity != nullptr);

        // -----------------------------------------------------------------------------
        // Check if we have reached the end of the current folder.
        // -----------------------------------------------------------------------------
        if (_pEntity->m_pNext != nullptr)
        {
            return _pEntity->m_pNext.get();
        }

        // -----------------------------------------------------------------------------
        // Check if there is a non-empty folder in the current region.
        // -----------------------------------------------------------------------------
        assert((_pEntity->m_pFolder != nullptr) && _pEntity->m_pFolder->m_pRegion != nullptr);

        for (int IndexOfFolder = _pEntity->m_pFolder->m_Type + 1; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
        {
            const CEntityFolder& rFolder = _pEntity->m_pFolder->m_pRegion->m_pEntityFolders[IndexOfFolder];

            if (rFolder.m_pEntities != nullptr)
            {
                return rFolder.m_pEntities.get();
            }
        }

        // -----------------------------------------------------------------------------
        // We have to search the next region.
        // -----------------------------------------------------------------------------
        int NextRegionIndex = _pEntity->m_pFolder->m_pRegion->m_ID + 1;

        for (int IndexOfRegion = NextRegionIndex; IndexOfRegion < s_MaxNumberOfRegions; IndexOfRegion++)
        {
            for (int IndexOfFolder = 0; IndexOfFolder < CMetaEntity::EType::NumberOfTypes; IndexOfFolder++)
            {
                const CEntityFolder& rFolder = m_pRegions[IndexOfRegion].m_pEntityFolders[IndexOfFolder];

                if (rFolder.m_pEntities != nullptr)
                {
                    return rFolder.m_pEntities.get();
                }
            }
        }

        return nullptr;
    }

} // namespace World

namespace World
{
    CEntityIterator::CEntityIterator(CEntity* _pEntity)
        : m_pCurrentEntity(_pEntity)
    {
    }

    CEntity& CEntityIterator::operator *  () const
    {
        assert(m_pCurrentEntity != nullptr);

        return *m_pCurrentEntity;
    }

    CEntity* CEntityIterator::operator -> () const
    {
        return m_pCurrentEntity;
    }

    CEntityIterator& CEntityIterator::Next()
    {
        m_pCurrentEntity = CMap::GetInstance().GetNextEntity(m_pCurrentEntity);

        return *this;
    }

    bool CEntityIterator::operator == (const CEntityIterator& _rOther)
    {
        return m_pCurrentEntity == _rOther.m_pCurrentEntity;
    }

    bool CEntityIterator::operator != (const CEntityIterator& _rOther)
    {
        return m_pCurrentEntity != _rOther.m_pCurrentEntity;
    }

} // namespace World
