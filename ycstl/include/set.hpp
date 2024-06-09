#pragma once

#include <set>

namespace ycstl {

template <typename... Args>
class ycset : std::set<Args> {
    constexpr bool is_sorted() const { return true; }
};

}  // namespace ycstl
