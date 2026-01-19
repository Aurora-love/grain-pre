#pragma once
#include <memory>

#ifdef _WIN32
    #ifdef _WIN64
        #define PLATFORM_WINDOWS
    #else
        #error "x86 Builds are not supported"
    #endif
#else   
    #error "Unknown platform"
#endif
//BUG: non-negative number
template<typename T>
constexpr auto BIT(T x) { return 1 << x; }

//绑定回调函数
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {\
        return this->fn(std::forward<decltype(args)>(args)...);\
    }
//TODO: ASSERT
//std::bind(&fn, this, std::placeholders::_1)

namespace GE {

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}
}