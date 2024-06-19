#pragma once

#include "exception.hpp"

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

    template <typename OutputContainer>
    OutputContainer getSetIntersection(const auto& rhs) const {
        if (false == isSorted()) {
            exception::YcException::ThrowWithMessage("Current container is not sorted");
        }
        if (false == rhs.isSorted()) {
            exception::YcException::ThrowWithMessage("Rhs container is not sorted");
        }
        auto outputContainer = OutputContainer {};
        const auto castedThis = static_cast<const T*>(this);
        (void)std::set_intersection(castedThis->cbegin(), castedThis->cend(), rhs.cbegin(), rhs.cend(),
                                    outputContainer.begin());
        return outputContainer;
    }
};

}  // namespace ycstl
