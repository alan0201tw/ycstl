#pragma once

namespace ycstl {

template <typename T>
class IYcContainer {
public:
    bool isSorted() const { return static_cast<const T*>(this)->isSorted(); }
    bool isUnique() const { return static_cast<const T*>(this)->isUnique(); }

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
