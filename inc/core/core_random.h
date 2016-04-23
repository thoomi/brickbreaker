////////////////////////////////////////////////////////////////////////////////
///
/// A C-Interface implementation for randomization functionality in order to 
/// easily use it in all other projects.
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Core
{
namespace Random
{
    int	GetRandomInt();
    int	GetRandomInt(int _Low, int _High);
    int GetRandomIntSign();

    float GetRandomFloat();
    float GetRandomFloat(float _Low, float _High);
    float GetRandomFloatSign();

} // namespace Random
} // namespace Core