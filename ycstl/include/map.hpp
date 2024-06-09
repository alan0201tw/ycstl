#pragma once

#include <map>

#include "common.hpp"

namespace ycstl {

template <typename... Args>
class YcMap : public std::map<Args...>, public YcCommon<YcMap<Args...>> {
public:
    static constexpr bool isSorted() { return true; }
    static constexpr bool isUnique() { return true; }
};

}  // namespace ycstl
