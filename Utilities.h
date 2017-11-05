#ifndef DSAA_UTILITIES_H
#define DSAA_UTILITIES_H

#include <cmath>
#include <chrono>
#include <random>
#include <type_traits>

namespace DSAA
{

namespace Utilities
{

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
