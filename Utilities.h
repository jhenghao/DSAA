#ifndef DSAA_UTILITIES_H
#define DSAA_UTILITIES_H

#include <chrono>
#include <cmath>
#include <random>
#include <type_traits>

#include "UtilitiesImpl.h"

namespace DSAA
{

namespace Utilities
{

// check whether an element exists in a container
//------------------------------------------------------------------------------
template <typename ElementT, typename ContainerT>
inline constexpr bool Exists (const ContainerT& container,
    const ElementT& element)
{
    return ExistsImpl<ContainerT, ElementT>::Exec(container, element);
}

// add an element if it does not exist in a container
//------------------------------------------------------------------------------
template <typename ElementT, typename ContainerT>
inline constexpr void AddIfNotExists (ContainerT& container, const ElementT& element)
{
    if (!ExistsImpl<ContainerT, ElementT>::Exec(container, element))
        container.push_back(element);
}

// get greatest common divisor of arguments a and b
//------------------------------------------------------------------------------
template <typename T>
inline constexpr T GCD (T a, T b)
{
    static_assert(std::is_integral<T>::value, "Integral required");
    return (0 == b) ? a : GCD(b, a % b);
}

// check if a floating number is integral
//------------------------------------------------------------------------------
template <typename T>
inline bool IsFloatingNumberIntegral (T value)
{
    T intPart;
    return 0 == std::modf(value, &intPart);
}

// Fisher-Yates shuffle
//------------------------------------------------------------------------------
template <typename IteratorT>
void Shuffle (IteratorT first, IteratorT end)
{
    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count());

    for (auto idx = (end - first) - 1; idx > 0; --idx)
    {
        std::uniform_int_distribution<decltype(idx)> distribution(0, idx);
        std::swap(first[idx], first[distribution(generator)]);
    }
}

} // namespace Utilities
} // namespace DSAA

#endif
