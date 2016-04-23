#pragma once

namespace Core
{
    class CClock
    {
        public:

            CClock(void);
            ~CClock(void);

        public:

            void Start();

        public:

            void  UpdateTime();
            float GetElapsedTime();

        private:
            
            double    m_Frequency;
            float     m_TimeSinceLastUpdate;
            long long m_LastTick;
            long long m_StartTick;
            
    };
} // namespace Core