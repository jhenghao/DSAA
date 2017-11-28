#ifndef DSAA_UTILITIES_H
#define DSAA_UTILITIES_H

#include <cassert>
#include <chrono>
#include <cmath>
#include <forward_list>
#include <list>
#include <map>
#include <random>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "UtilitiesImpl.h"

namespace DSAA
{

namespace Utilities
{

// check whether an element exists in a container (linear time)
//------------------------------------------------------------------------------
template<
    template <typename...> class ContainerT,
    typename ElementT,
    typename... Args,
    typename std::enable_if<
        std::is_same<ContainerT<Args...>, std::vector<Args...>>::value |
        std::is_same<ContainerT<Args...>, std::list<Args...>>::value |
        std::is_same<ContainerT<Args...>, std::forward_list<Args...>>::value
    >::type* = nullptr>
bool Exists (const ContainerT<Args...>& container, const ElementT& element)
{
    return (container.cend() != 
        std::find(container.cbegin(), container.cend(), element));
}

// check whether an element exists in a container (log or const time)
//------------------------------------------------------------------------------
template<
    template <typename...> class ContainerT,
    typename ElementT,
    typename... Args,
    typename std::enable_if<
        std::is_same<ContainerT<Args...>, std::map<Args...>>::value |
        std::is_same<ContainerT<Args...>, std::unordered_map<Args...>>::value |
        std::is_same<ContainerT<Args...>, std::set<Args...>>::value |
        std::is_same<ContainerT<Args...>, std::unordered_set<Args...>>::value
    >::type* = nullptr>
bool Exists (const ContainerT<Args...>& container, const ElementT& element)
{
    return container.cend() != container.find(element);
}

// add an element if it does not exist in a container
//------------------------------------------------------------------------------
template <typename ElementT, typename ContainerT>
inline constexpr void AddIfNotExists (ContainerT& container, const ElementT& element)
{
    if (!Exists(container, element))
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
