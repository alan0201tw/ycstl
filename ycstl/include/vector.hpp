#pragma once

#include <algorithm>
#include <vector>

#include "common.hpp"

namespace ycstl {

template <typename... Args>
class YcSortedVector;

template <typename... Args>
class YcVector : public std::vector<Args...>, public YcCommon<YcSet<Args...>> {
public:
    template <typename... CtorArgs>
    YcVector(CtorArgs&&... ctorArgs) : std::vector<Args...>(std::forward<CtorArgs>(ctorArgs)...) {}

    static constexpr bool isSorted() { return false; }
    static constexpr bool isUnique() { return false; }

    auto getSortedVector() const {
        auto sortedVector = YcSortedVector<Args...> {*this};
        std::sort(sortedVector.begin(), sortedVector.end());
        return sortedVector;
    }
};

template <typename... Args>
class YcSortedVector : public YcVector<Args...> {
public:
    static constexpr bool isSorted() { return true; }
    static constexpr bool isUnique() { return false; }

private:
    template <typename... CtorArgs>
    YcSortedVector(CtorArgs&&... ctorArgs) : YcVector<Args...>(std::forward<CtorArgs>(ctorArgs)...) {}

    friend class YcVector<Args...>;
};

}  // namespace ycstl
