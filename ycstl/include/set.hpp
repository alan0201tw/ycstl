#pragma once

#include <set>

#include "common.hpp"

namespace ycstl {

template <typename... Args>
class YcSet : public std::set<Args...>, public yccommon<YcSet<Args...>> {
public:
    static constexpr bool isSorted() { return true; }
    static constexpr bool isUnique() { return true; }
};

}  // namespace ycstl
