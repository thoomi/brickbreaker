#pragma once

#include "core_vector3.h"

namespace Core
{
	class CAABB3
	{
        public:

            struct CollisionInfo
            {
                float    m_Time;
                CVector3 m_Normal;
            };

		public:

			CAABB3();
			CAABB3(const CAABB3& _rAABB);
            CAABB3(const CVector3& _rCenter, float _Size);
            CAABB3(const CVector3& _rCenter, float _Width, float _Height, float _Length);
			
        public:

            CAABB3& operator = (const CAABB3& _rAABB);

		public:

			bool Intersects(const CAABB3& _rAABB) const;
			bool Contains(const CAABB3& _rAABB) const;

		public:

			CAABB3 Union(const CAABB3& _rAABB) const;
            
        public:

            float GetExtentX() const;
            float GetExtentY() const;
            float GetExtentZ() const;
            
            CVector3 GetExtents() const;

        public:

            CVector3 GetCenter() const;

        public:

            CollisionInfo GetCollisionInfo(const CAABB3& _rAABB, const Core::CVector3& _rMovementVector) const;

        public:

            bool IsValid() const;

		public:

			CVector3 m_Min;
			CVector3 m_Max;
	};
} // namespace Core