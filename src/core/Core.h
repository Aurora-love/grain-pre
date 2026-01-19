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
//std::bind(&fn, this, std::placeholders::_1)
//ASSERT 仅在 Debug 模式或显式开启 ASSERTS_ENABLE 时有效
#ifdef ASSERTS_ENABLE
	#define ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ASSERT_ENGINE(x, ...) { if(!(x)) { LOG_ERROR_ENGINE("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ASSERT(x, ...)
	#define ASSERT_ENGINE(x, ...)
#endif

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