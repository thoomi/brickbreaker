#include "core/core_random.h"

#include <cstdlib>
#include <ctime>

namespace
{
    class CCoreRandom
    {
        public:

            CCoreRandom()
            {
                srand(static_cast<int>(time(nullptr)));
            }

            ~CCoreRandom()
            {
            }

        public:

            int	GetRandomInt()
            {
                return rand();
            }

            int	GetRandomInt(int _Low, int _High)
            {
                return _Low + (GetRandomInt() % (_High - _Low));
            }

            int GetRandomIntSign()
            {
                if (GetRandomInt() > (RAND_MAX / 2))
                {
                    return -1;
                }

                return 1;
            }

            float GetRandomFloat()
            {
                return static_cast<float>(GetRandomInt() / static_cast<float>(RAND_MAX));
            }

            float GetRandomFloat(float _Low, float _High)
            {
                return _Low + (GetRandomFloat() * (_High - _Low));
            }

            float GetRandomFloatSign()
            {
                if (GetRandomFloat() > 0.5f)
                {
                    return -1.0f;
                }

                return 1.0f;
            }
    };
}


namespace
{
    CCoreRandom g_Randomizer;
}


namespace Core
{
namespace Random
{
    int	GetRandomInt()
    {
        return g_Randomizer.GetRandomInt();
    }

    int	GetRandomInt(int _Low, int _High)
    {
        return g_Randomizer.GetRandomInt(_Low, _High);
    }

    int GetRandomIntSign()
    {
        return g_Randomizer.GetRandomIntSign();
    }

    float GetRandomFloat()
    {
        return g_Randomizer.GetRandomFloat();
    }

    float GetRandomFloat(float _Low, float _High)
    {
        return g_Randomizer.GetRandomFloat(_Low, _High);
    }

    float GetRandomFloatSign()
    {
        return g_Randomizer.GetRandomFloatSign();
    }

} // namespace Random
} // namespace Core