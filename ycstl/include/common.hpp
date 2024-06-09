#pragma once

namespace ycstl {

template <typename T>
class yccommon {
    static constexpr bool isSorted() { return T::isSorted(); }
    static constexpr bool isUnique() { return T::isUnique(); }
};

}  // namespace ycstl
