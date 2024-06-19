#pragma once

#include <algorithm>
#include <vector>

#include "common.hpp"
#include "macro.hpp"

namespace ycstl {

template <typename... Args>
class YcSortedVector;

template <typename... Args>
class YcVector : public IYcContainer<YcVector<Args...>> {
public:
    template <typename... CtorArgs>
    YcVector(CtorArgs&&... ctorArgs) : m_vector(std::forward<CtorArgs>(ctorArgs)...), m_isSorted {false} {}
    template <class T>
    YcVector(std::initializer_list<T>&& ctorArgs) : m_vector(ctorArgs), m_isSorted {false} {}

    bool isSorted() const { return m_isSorted; }
    static constexpr bool isUnique() { return false; }

    void sort() {
        std::sort(m_vector.begin(), m_vector.end());
        m_isSorted = true;
    }
    auto getSortedVector() const {
        auto copiedVector = m_vector;
        std::sort(copiedVector.begin(), copiedVector.end());
        return YcSortedVector<Args...> {std::move(copiedVector)};
    }

    IMPL_ITERABLE(m_vector)
    IMPL_DELEGATE_METHOD_WITH_HOOK(m_vector, emplace_back, markDirty)
    IMPL_CONST_DELEGATE_METHOD(m_vector, size)
    IMPL_CONST_DELEGATE_METHOD(m_vector, at)
    IMPL_CONST_DELEGATE_METHOD(m_vector, capacity)
    IMPL_DELEGATE_METHOD(m_vector, at)
    IMPL_DELEGATE_METHOD(m_vector, reserve)
    IMPL_DELEGATE_METHOD(m_vector, resize)
    IMPL_DELEGATE_METHOD(m_vector, erase)

private:
    void markDirty() { m_isSorted = false; }

    std::vector<Args...> m_vector;
    bool m_isSorted;
};

template <typename... Args>
class YcSortedVector : public IYcContainer<YcSortedVector<Args...>> {
public:
    static constexpr bool isSorted() { return true; }
    static constexpr bool isUnique() { return false; }

    IMPL_CONST_ITERABLE(m_sortedVector)
    IMPL_CONST_DELEGATE_METHOD(m_sortedVector, size)
    IMPL_CONST_DELEGATE_METHOD(m_sortedVector, at)
    IMPL_CONST_DELEGATE_METHOD(m_sortedVector, capacity)
    IMPL_DELEGATE_METHOD(m_sortedVector, reserve)
    IMPL_DELEGATE_METHOD(m_sortedVector, resize)
    IMPL_DELEGATE_METHOD(m_sortedVector, erase)  // Erasing from a sorted vector maintains its order

private:
    template <typename... CtorArgs>
    YcSortedVector(CtorArgs&&... ctorArgs) : m_sortedVector(std::forward<CtorArgs>(ctorArgs)...) {}

    friend class YcVector<Args...>;

    std::vector<Args...> m_sortedVector;
};

}  // namespace ycstl
