#pragma once

namespace Core
{
	class CVector3
	{
        public:

            enum
            {
                X,
                Y,
                Z
            };


		public:

			static const int s_NumberOfComponents = 3;

		public:

			CVector3();
			CVector3(const CVector3& _rVector);
			CVector3(float _Value1, float _Value2, float _Value3);
			
		public:

			CVector3& operator = (const CVector3& _rVector);

		public:

			float& operator [] (const int _Index);
			const float& operator [] (const int _Index) const;

		public:

            CVector3& operator += (const CVector3& _rVector);
            CVector3& operator -= (const CVector3& _rVector);

            CVector3& operator *= (const float _Scalar);
            CVector3& operator /= (const float _Scalar);

			CVector3 operator + (const CVector3& _rVector) const;
			CVector3 operator - (const CVector3& _rVector) const;

			CVector3 operator * (const float _Scalar) const;
			CVector3 operator / (const float _Scalar) const;

		public:

			bool operator == (const CVector3& _rVector) const;
			bool operator != (const CVector3& _rVector) const;
			bool operator <  (const CVector3& _rVector) const;
			bool operator <= (const CVector3& _rVector) const;
			bool operator >  (const CVector3& _rVector) const;
			bool operator >= (const CVector3& _rVector) const;

        public:

            float GetDotProduct(const CVector3& _rVector);
            float GetLength();

            CVector3& Normalize();

		private:

			float m_Values[s_NumberOfComponents];
	};
} // namespace Core