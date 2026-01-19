#pragma once
#include "core/Core.h"
#include "core/events/Event.h"
#include <string>
#include <functional>
namespace GE {

struct WindowProps {
    std::string m_Title;
    uint32_t m_Width;
    uint32_t m_Height;
    WindowProps(const std::string& title = "Grain Engine", 
                uint32_t width = 1600, uint32_t height = 900)
                : m_Title(title), m_Width(width), m_Height(height) {}
};

class IWindow {
public:
    using EventCallbackFn = std::function<void(Event&)>;
    virtual ~IWindow() = default;
    virtual void Update() = 0;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
/**
 * @brief 获取底层的原生窗口句柄（GLFWwindow*）
 * @return 返回一个指向底层原生窗口对象的指针，调用者不应该删除此指针，其生命周期由窗口对象管理。
 */
    virtual void* GetNativeWindow() const = 0;
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    static Scope<IWindow> CreateWindow(const WindowProps& props = WindowProps());
};
}