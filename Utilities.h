#ifndef DSAA_UTILITIES_H
#define DSAA_UTILITIES_H

#include <cmath>
#include <type_traits>

namespace DSAA
{

class Utilities
{

public:
    // get greatest common divisor of arguments a and b
    template <typename T>
    static inline constexpr T GCD (T a, T b);

    // check if a floating number is integral
    template <typename T>
    static inline bool IsFloatingNumberIntegral (T value);
};

template <typename T>
constexpr T Utilities::GCD (T a, T b)
{
    static_assert(std::is_integral<T>::value, "Integral required");
    return (0 == b) ? a : GCD(b, a % b);
}

template <typename T>
bool Utilities::IsFloatingNumberIntegral (T value)
{
    T intPart;
    return 0 == std::modf(value, &intPart);
}

}

#endif
