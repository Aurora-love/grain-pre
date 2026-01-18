#pragma once
#include "Event.h"
#include <sstream>
namespace GE {

class KeyEvent : public Event {
public:
    inline int GetKeyCode() const { return m_KeyCode; }
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
protected:
    KeyEvent(int keycode) : m_KeyCode(keycode) {}
    int m_KeyCode;
};
/** @brief 按键按下事件 */
class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
    inline int GetRepeatCount() const { return m_RepeatCount; }
    EVENT_CLASS_TYPE(KeyPressed)
//OPTIMIZE
	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}
private:
    int m_RepeatCount;
};
/** @brief 按键释放事件 */
class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
    EVENT_CLASS_TYPE(KeyReleased)
//OPTIMIZE
    std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}
};
/** @brief 键盘输入字符事件 */
class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
    EVENT_CLASS_TYPE(KeyTyped)
//OPTIMIZE
	std::string ToString() const override {
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}
};
}