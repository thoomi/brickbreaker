#include "core\core_vector3.h"

#include <assert.h>
#include <math.h>

namespace Core
{
	CVector3::CVector3()
	{
		m_Values[X] = 0.0f;
		m_Values[Y] = 0.0f;
		m_Values[Z] = 0.0f;
	}

	CVector3::CVector3(const CVector3& _rVector)
	{
        m_Values[X] = _rVector.m_Values[X];
        m_Values[Y] = _rVector.m_Values[Y];
        m_Values[Z] = _rVector.m_Values[Z];
	}

	CVector3::CVector3(float _Value1, float _Value2, float _Value3)
	{
        m_Values[X] = _Value1;
        m_Values[Y] = _Value2;
        m_Values[Z] = _Value3;
	}

	CVector3& CVector3::operator = (const CVector3& _rVector)
	{
        m_Values[X] = _rVector.m_Values[X];
        m_Values[Y] = _rVector.m_Values[Y];
        m_Values[Z] = _rVector.m_Values[Z];

		return *this;
	}

	float& CVector3::operator [] (const int _Index)
	{
		assert(_Index < s_NumberOfComponents);

		return m_Values[_Index];
	}

	const float& CVector3::operator [] (const int _Index) const
	{
		assert(_Index < s_NumberOfComponents);

		return m_Values[_Index];
	}

    CVector3& CVector3::operator += (const CVector3& _rVector)
    {
        m_Values[X] += _rVector.m_Values[X];
        m_Values[Y] += _rVector.m_Values[Y];
        m_Values[Z] += _rVector.m_Values[Z];

        return *this;
    }

    CVector3& CVector3::operator -= (const CVector3& _rVector)
    {
        m_Values[X] -= _rVector.m_Values[X];
        m_Values[Y] -= _rVector.m_Values[Y];
        m_Values[Z] -= _rVector.m_Values[Z];

        return *this;
    }

    CVector3& CVector3::operator *= (const float _Scalar)
    {
        m_Values[X] *= _Scalar;
        m_Values[Y] *= _Scalar;
        m_Values[Z] *= _Scalar;

        return *this;
    }

    CVector3& CVector3::operator /= (const float _Scalar)
    {
        m_Values[X] /= _Scalar;
        m_Values[Y] /= _Scalar;
        m_Values[Z] /= _Scalar;

        return *this;
    }

	CVector3 CVector3::operator + (const CVector3& _rVector) const
	{
		CVector3 Vector;

        Vector.m_Values[X] = m_Values[X] + _rVector.m_Values[X];
        Vector.m_Values[Y] = m_Values[Y] + _rVector.m_Values[Y];
        Vector.m_Values[Z] = m_Values[Z] + _rVector.m_Values[Z];

		return Vector;
	}

	CVector3 CVector3::operator - (const CVector3& _rVector) const
	{
		CVector3 Vector;

        Vector.m_Values[X] = m_Values[X] - _rVector.m_Values[X];
        Vector.m_Values[Y] = m_Values[Y] - _rVector.m_Values[Y];
        Vector.m_Values[Z] = m_Values[Z] - _rVector.m_Values[Z];

		return Vector;
	}

	CVector3 CVector3::operator * (const float _Scalar) const
	{
		CVector3 Vector;

        Vector.m_Values[X] = m_Values[X] * _Scalar;
        Vector.m_Values[Y] = m_Values[Y] * _Scalar;
        Vector.m_Values[Z] = m_Values[Z] * _Scalar;

		return Vector;
	}

	CVector3 CVector3::operator / (const float _Scalar) const
	{
		CVector3 Vector;

		assert(_Scalar != 0.0f);

        Vector.m_Values[X] = m_Values[X] / _Scalar;
        Vector.m_Values[Y] = m_Values[Y] / _Scalar;
        Vector.m_Values[Z] = m_Values[Z] / _Scalar;

		return Vector;
	}

	bool CVector3::operator == (const CVector3& _rVector) const
	{
		return ((m_Values[X] == _rVector.m_Values[X]) && 
			    (m_Values[Y] == _rVector.m_Values[Y]) &&
				(m_Values[Z] == _rVector.m_Values[Z]));
	}

	bool CVector3::operator != (const CVector3& _rVector) const
	{
		return ((m_Values[X] != _rVector.m_Values[X]) ||
			    (m_Values[Y] != _rVector.m_Values[Y]) ||
				(m_Values[Z] != _rVector.m_Values[Z]));
	}

	bool CVector3::operator < (const CVector3& _rVector) const
	{
		return ((m_Values[X] < _rVector.m_Values[X]) &&
			    (m_Values[Y] < _rVector.m_Values[Y]) &&
			    (m_Values[Z] < _rVector.m_Values[Z]));
	}

	bool CVector3::operator <= (const CVector3& _rVector) const
	{
		return ((m_Values[X] <= _rVector.m_Values[X]) &&
			    (m_Values[Y] <= _rVector.m_Values[Y]) &&
			    (m_Values[Z] <= _rVector.m_Values[Z]));
	}

	bool CVector3::operator > (const CVector3& _rVector) const
	{
		return ((m_Values[X] > _rVector.m_Values[X]) &&
			    (m_Values[Y] > _rVector.m_Values[Y]) &&
			    (m_Values[Z] > _rVector.m_Values[Z]));
	}

	bool CVector3::operator >= (const CVector3& _rVector) const
	{
		return ((m_Values[X] >= _rVector.m_Values[X]) &&
			    (m_Values[Y] >= _rVector.m_Values[Y]) &&
			    (m_Values[Z] >= _rVector.m_Values[Z]));
	}

    float CVector3::GetDotProduct(const CVector3& _rVector)
	{
        return m_Values[X] * _rVector[X] + m_Values[Y] * _rVector[Y] + m_Values[Z] * _rVector[Z];
	}

    float CVector3::GetLength()
	{
        return sqrt(GetDotProduct(*this));
	}

    CVector3& CVector3::Normalize()
	{
        float Length = GetLength();

        assert(Length > 0);

        float InverseLength = 1.0f / Length;

        m_Values[X] *= InverseLength;
        m_Values[Y] *= InverseLength;
        m_Values[Z] *= InverseLength;

        return *this;
	}
} // namespace Core