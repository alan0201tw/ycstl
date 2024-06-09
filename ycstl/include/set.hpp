#pragma once

#include <set>

#include "common.hpp"

namespace ycstl {

template <typename... Args>
class YcSet : public std::set<Args...>, public YcCommon<YcSet<Args...>> {
public:
    template <typename... CtorArgs>
    YcSet(CtorArgs&&... ctorArgs) : std::set<Args...>(std::forward<CtorArgs>(ctorArgs)...) {}
    template <class T>
    YcSet(std::initializer_list<T>&& ctorArgs) : std::set<Args...>(ctorArgs) {}

    static constexpr bool isSorted() { return true; }
    static constexpr bool isUnique() { return true; }
};

}  // namespace ycstl
