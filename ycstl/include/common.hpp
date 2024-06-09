#pragma once

namespace ycstl {

template <typename T>
class YcCommon {
    static constexpr bool isSorted() { return T::isSorted(); }
    static constexpr bool isUnique() { return T::isUnique(); }
};

}  // namespace ycstl
