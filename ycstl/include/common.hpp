#pragma once

namespace ycstl {

template <typename T>
class YcCommon {
public:
    static constexpr bool isSorted() { return T::isSorted(); }
    static constexpr bool isUnique() { return T::isUnique(); }

    bool isSubsetOf(const auto& rhs) const {
        const auto castedThis = static_cast<const T*>(this);
        for (const auto& entry : *castedThis) {
            if (false == rhs.contains(entry)) {
                return false;
            }
        }
        return true;
    }
};

}  // namespace ycstl
