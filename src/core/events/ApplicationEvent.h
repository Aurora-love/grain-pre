#pragma once
#include "Event.h"
#include <sstream>
namespace GE {

/** @brief 窗口关闭事件 */
class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
/** @brief 窗口大小调整事件 */
class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}
	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
//OPTIMIZE​
	std::string ToString() const override {
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}
private:
	uint32_t m_Width, m_Height;
};
/** @brief 窗口获得焦点事件 */
class WindowFocusEvent : public Event {
public:
	WindowFocusEvent() = default;
	EVENT_CLASS_TYPE(WindowFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
/** @brief 窗口失去焦点事件 */
class WindowLostFocusEvent : public Event {
public:
	WindowLostFocusEvent() = default;
	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
/** @brief 窗口移动事件 */
class WindowMovedEvent : public Event {
public:
	WindowMovedEvent(int x, int y) : m_X(x), m_Y(y) {}
	inline int GetX() const { return m_X; }
	inline int GetY() const { return m_Y; }
    EVENT_CLASS_TYPE(WindowMoved)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
//OPTIMIZE​
	std::string ToString() const override {
		std::stringstream ss;
		ss << "WindowMovedEvent: " << m_X << ", " << m_Y;
		return ss.str();
	}
private:
	int m_X, m_Y;
 };
}