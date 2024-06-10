#pragma once

namespace ycstl {

#define IMPL_CONST_ITERABLE(proxy)                \
    auto cbegin() const { return proxy.begin(); } \
    auto cend() const { return proxy.end(); }     \
    auto begin() const { return proxy.begin(); }  \
    auto end() const { return proxy.end(); }

#define IMPL_ITERABLE(proxy)               \
    auto begin() { return proxy.begin(); } \
    auto end() { return proxy.end(); }     \
    IMPL_CONST_ITERABLE(proxy)

#define IMPL_DELEGATE_METHOD(proxy, method)                     \
    template <typename... MethodArgs>                           \
    auto method(MethodArgs&&... args) {                         \
        return proxy.method(std::forward<MethodArgs>(args)...); \
    }

#define IMPL_DELEGATE_METHOD_WITH_HOOK(proxy, method, hook)     \
    template <typename... MethodArgs>                           \
    auto method(MethodArgs&&... args) {                         \
        hook();                                                 \
        return proxy.method(std::forward<MethodArgs>(args)...); \
    }

#define IMPL_CONST_DELEGATE_METHOD(proxy, method)               \
    template <typename... MethodArgs>                           \
    auto method(MethodArgs&&... args) const {                   \
        return proxy.method(std::forward<MethodArgs>(args)...); \
    }

}  // namespace ycstl