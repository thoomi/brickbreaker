#pragma once

namespace Algo
{
    template <class T>
    const T& Max(const T& _rLhs, const T& _rRhs) 
    {
        return (_rLhs < _rRhs) ? _rRhs : _rLhs;
    }

    template <class T>
    const T& Min(const T& _rLhs, const T& _rRhs)
    {
        return (_rLhs < _rRhs) ? _rLhs : _rRhs;
    }

    template <class T>
    const T& Clamp(const T& _rValue, const T& _rMin, const T& _rMax)
    {
        return Max<T>(_rMin, Min<T>(_rValue, _rMax));
    }

    template <class T>
    T Sign(const T& _rValue)
    {
        return _rValue < T(-0) ? T(-1) : T(1);
    }
    
} // namespace Core