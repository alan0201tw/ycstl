#pragma once

#include <exception>
#include <string>

namespace ycstl {
namespace exception {

class YcException : public std::exception {
public:
    template <typename... WhatArgs>
    static void ThrowWithMessage(WhatArgs&&... whatArgs) {
        throw YcException(std::forward<WhatArgs>(whatArgs)...);
    }

    virtual const char* what() const noexcept override { return _whatStr.c_str(); }

private:
    template <typename... WhatArgs>
    YcException(WhatArgs&&... whatArgs) : _whatStr(std::forward<WhatArgs>(whatArgs)...) {}

    const std::string _whatStr;
};

}  // namespace exception
}  // namespace ycstl