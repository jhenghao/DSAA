#ifndef DSAA_UTILITIESIMPL_H
#define DSAA_UTILITIESIMPL_H

#include <cassert>
#include <map>
#include <vector>

namespace DSAA
{

namespace Utilities
{

//------------------------------------------------------------------------------
template<template<typename...> class StdContainerT, typename UnknownContainerT>
struct IsSameContainerType : std::false_type {};

//------------------------------------------------------------------------------
template<template<typename...> class StdContainerT, typename... Args>
struct IsSameContainerType<StdContainerT, StdContainerT<Args...>> : std::true_type {};

// check whether container is a vector
//------------------------------------------------------------------------------
template <typename ContainerT>
inline constexpr bool IsStdVector (const ContainerT&)
{
    return IsSameContainerType<std::vector, ContainerT>::value;
}

// check whether container is a map
//------------------------------------------------------------------------------
template <typename ContainerT>
inline constexpr bool IsStdMap (const ContainerT&)
{
    return IsSameContainerType<std::map, ContainerT>::value;
}

//------------------------------------------------------------------------------
template <typename ContainerT, typename ElementT>
inline constexpr bool ExistsLinear (const ContainerT& container, const ElementT& element)
{
    return (container.cend() != 
        std::find(container.cbegin(), container.cend(), element));
}

//------------------------------------------------------------------------------
template <typename ContainerT, typename ElementT>
inline constexpr bool ExistsNonLinear (const ContainerT& container, const ElementT& element)
{
    return container.cend() != container.find(element);
}

//------------------------------------------------------------------------------
template <typename ContainerT, typename ElementT>
struct ExistsImpl
{
    static bool Exec (const ContainerT& container, const ElementT& element)
    {
        assert(false);
        return false;
    }
};

//------------------------------------------------------------------------------
template <typename ElementT, typename... Args>
struct ExistsImpl<std::vector<Args...>, ElementT>
{
    static bool Exec (const std::vector<Args...>& container, const ElementT& element)
    {
        return ExistsLinear(container, element);
    }
};

//------------------------------------------------------------------------------
template <typename ElementT, typename... Args>
struct ExistsImpl<std::map<Args...>, ElementT>
{
    static bool Exec (const std::map<Args...>& container, const ElementT& element)
    {
        return ExistsNonLinear(container, element);
    }
};

} // namespace Utilities
} // namespace DSAA

#endif
