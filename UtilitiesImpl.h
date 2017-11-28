#ifndef DSAA_UTILITIESIMPL_H
#define DSAA_UTILITIESIMPL_H

#include <vector>
#include <map>

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

} // namespace Utilities
} // namespace DSAA

#endif
