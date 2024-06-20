#pragma once

#include "exception.hpp"

namespace ycstl {

template <typename T>
class IYcContainer {
private:
#define GEN_RANGE_METHOD(yc_method, std_method)                                                         \
    template <typename OutputContainer>                                                                 \
    OutputContainer yc_method(const auto& rhs) const {                                                  \
        if (false == isSorted()) {                                                                      \
            exception::YcException::ThrowWithMessage("Current container is not sorted");                \
        }                                                                                               \
        if (false == rhs.isSorted()) {                                                                  \
            exception::YcException::ThrowWithMessage("Rhs container is not sorted");                    \
        }                                                                                               \
        auto outputContainer = OutputContainer {};                                                      \
        const auto inserter = std::back_inserter(outputContainer);                                      \
        const auto castedThis = static_cast<const T*>(this);                                            \
        (void)std_method(castedThis->cbegin(), castedThis->cend(), rhs.cbegin(), rhs.cend(), inserter); \
        return outputContainer;                                                                         \
    }

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

    GEN_RANGE_METHOD(getSetUnion, std::set_union);
    GEN_RANGE_METHOD(getSetIntersection, std::set_intersection);
    GEN_RANGE_METHOD(getSetDifference, std::set_difference);
    GEN_RANGE_METHOD(getSetSymmetricDifference, std::set_symmetric_difference);

#undef GEN_RANGE_METHOD
};

}  // namespace ycstl
