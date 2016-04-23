#include "core/core_aabb3.h"
#include "core/core_algorithm.h"

#include <assert.h>

namespace Core
{
	CAABB3::CAABB3()
        : m_Min ()
        , m_Max ()
	{
	}

	CAABB3::CAABB3(const CAABB3& _rAABB)
        : m_Min(_rAABB.m_Min)
        , m_Max(_rAABB.m_Max)
	{
	}

    CAABB3::CAABB3(const CVector3& _rCenter, float _Size)
        : m_Min()
        , m_Max()
    {
        float HalfSize = _Size * 0.5f;

        m_Min[CVector3::X] = _rCenter[CVector3::X] - HalfSize;
        m_Min[CVector3::Y] = _rCenter[CVector3::Y] - HalfSize;
        m_Min[CVector3::Z] = _rCenter[CVector3::Z] - HalfSize;

        m_Max[CVector3::X] = _rCenter[CVector3::X] + HalfSize;
        m_Max[CVector3::Y] = _rCenter[CVector3::Y] + HalfSize;
        m_Max[CVector3::Z] = _rCenter[CVector3::Z] + HalfSize;
    }

    CAABB3::CAABB3(const CVector3& _rCenter, float _Width, float _Height, float _Length) 
        : m_Min ()
        , m_Max ()
	{
        float HalfWidth  = _Width  * 0.5f;
        float HalfHeight = _Height * 0.5f;
        float HalfLength = _Length * 0.5f;

        m_Min[CVector3::X] = _rCenter[CVector3::X] - HalfWidth;
        m_Min[CVector3::Y] = _rCenter[CVector3::Y] - HalfHeight;
        m_Min[CVector3::Z] = _rCenter[CVector3::Z] - HalfLength;

        m_Max[CVector3::X] = _rCenter[CVector3::X] + HalfWidth;
        m_Max[CVector3::Y] = _rCenter[CVector3::Y] + HalfHeight;
        m_Max[CVector3::Z] = _rCenter[CVector3::Z] + HalfLength;
	}

    CAABB3& CAABB3::operator = (const CAABB3& _rAABB)
    {
        m_Min = _rAABB.m_Min;
        m_Max = _rAABB.m_Max;

        return *this;
    }

	bool CAABB3::Intersects(const CAABB3& _rAABB) const
	{
        assert(IsValid() && _rAABB.IsValid());

		return !((m_Max[CVector3::X] < _rAABB.m_Min[CVector3::X]) ||
				 (m_Max[CVector3::Y] < _rAABB.m_Min[CVector3::Y]) ||
				 (m_Max[CVector3::Z] < _rAABB.m_Min[CVector3::Z]) ||
				 (m_Min[CVector3::X] > _rAABB.m_Max[CVector3::X]) ||
				 (m_Min[CVector3::Y] > _rAABB.m_Max[CVector3::Y]) ||
			     (m_Min[CVector3::Z] > _rAABB.m_Max[CVector3::Z]));
	}

	bool CAABB3::Contains(const CAABB3& _rAABB) const
	{
        assert(IsValid() && _rAABB.IsValid());

		return !((m_Max[CVector3::X] < _rAABB.m_Min[CVector3::X]) &&
				 (m_Max[CVector3::Y] < _rAABB.m_Min[CVector3::Y]) &&
				 (m_Max[CVector3::Z] < _rAABB.m_Min[CVector3::Z]) &&
				 (m_Min[CVector3::X] > _rAABB.m_Max[CVector3::X]) &&
				 (m_Min[CVector3::Y] > _rAABB.m_Max[CVector3::Y]) &&
				 (m_Min[CVector3::Z] > _rAABB.m_Max[CVector3::Z]));
	}

	CAABB3 CAABB3::Union(const CAABB3& _rAABB) const
	{
		CAABB3 Unioned;

		for (int Index = 0; Index < CVector3::s_NumberOfComponents; Index++)
		{
			if (m_Min[Index] < _rAABB.m_Min[Index])
			{
				Unioned.m_Min[Index] = m_Min[Index];
			}
			else
			{
				Unioned.m_Min[Index] = _rAABB.m_Min[Index];
			}

			if (m_Max[Index] < _rAABB.m_Max[Index])
			{
				Unioned.m_Max[Index] = m_Max[Index];
			}
			else
			{
				Unioned.m_Max[Index] = _rAABB.m_Max[Index];
			}
		}

		return Unioned;
	}

    float CAABB3::GetExtentX() const
	{
        assert(IsValid());

        return (m_Max[CVector3::X] - m_Min[CVector3::X]) * 0.5f;
	}

    float CAABB3::GetExtentY() const
	{
        assert(IsValid());

        return (m_Max[CVector3::Y] - m_Min[CVector3::Y]) * 0.5f;
	}

    float CAABB3::GetExtentZ() const
	{
        assert(IsValid());

        return (m_Max[CVector3::Z] - m_Min[CVector3::Z]) * 0.5f;
	}

    CVector3 CAABB3::GetExtents() const
	{
        return CVector3(GetExtentX(), GetExtentY(), GetExtentZ());
	}

    CVector3 CAABB3::GetCenter() const
	{
        return CVector3((m_Min + m_Max) * 0.5f);
	}

    CAABB3::CollisionInfo CAABB3::GetCollisionInfo(const CAABB3& _rAABB, const Core::CVector3& _rMovementVector) const
	{
        Core::CVector3 OtherPosition = _rAABB.GetCenter();
        Core::CVector3 OtherExtents  = _rAABB.GetExtents();
        Core::CVector3 Position      = GetCenter();
        Core::CVector3 Extents       = GetExtents();

        float ScaleX = 1.0f / _rMovementVector[0];
        float ScaleY = 1.0f / _rMovementVector[1];
        float ScaleZ = 1.0f / _rMovementVector[2];

        float SignX = Algo::Sign(ScaleX);
        float SignY = Algo::Sign(ScaleY);
        float SignZ = Algo::Sign(ScaleZ);

        float NearTimeX = (Position[0] - SignX * (Extents[0] + OtherExtents[0]) - OtherPosition[0]) * ScaleX;
        float NearTimeY = (Position[1] - SignY * (Extents[1] + OtherExtents[1]) - OtherPosition[1]) * ScaleY;
        float NearTimeZ = (Position[2] - SignZ * (Extents[2] + OtherExtents[2]) - OtherPosition[2]) * ScaleZ;

        float FarTimeX  = (Position[0] + SignX * (Extents[0] + OtherExtents[0]) - OtherPosition[0]) * ScaleX;
        float FarTimeY  = (Position[1] + SignY * (Extents[1] + OtherExtents[1]) - OtherPosition[1]) * ScaleY;
        float FarTimeZ  = (Position[2] + SignZ * (Extents[2] + OtherExtents[2]) - OtherPosition[2]) * ScaleZ;

        float HitTime = 1.0f;

        if (!(NearTimeX > FarTimeY ||
              NearTimeX > FarTimeZ ||
              NearTimeY > FarTimeX ||
              NearTimeY > FarTimeZ ||
              NearTimeZ > FarTimeX ||
              NearTimeZ > FarTimeY
              ))
        {
            float NearTime = Algo::Max(Algo::Max(NearTimeX, NearTimeY), NearTimeZ);
            float FarTime  = Algo::Min(Algo::Min(FarTimeX, FarTimeY), FarTimeZ);

            if (!(NearTime >= 1.0f || FarTime <= 0.0f))
            {
                HitTime = Algo::Clamp(NearTime - 0.0001f, 0.0f, 1.0f);
            }
        }

        
        CollisionInfo Info;
        Info.m_Time   = HitTime;

        if (NearTimeX > NearTimeY)
        {
            Info.m_Normal[0] = -SignX;
        }
        else
        {
            Info.m_Normal[1] = -SignY;
        }


        return Info;
	}

    bool CAABB3::IsValid() const
    {
        return (m_Max[CVector3::X] >= m_Min[CVector3::X]) && 
               (m_Max[CVector3::Y] >= m_Min[CVector3::Y]) && 
               (m_Max[CVector3::Z] >= m_Min[CVector3::Z]);
    }
} // namespace Core