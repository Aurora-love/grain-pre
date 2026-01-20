#pragma once
#include "core/Core.h"

namespace GE {
//轮询
class Input {
public:
	virtual ~Input() = default;
	inline static bool IsKeyPressed(uint32_t keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
	inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
	
	inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
	inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	
	inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
protected:
	virtual bool IsKeyPressedImpl(uint32_t keycode) = 0;
	virtual bool IsMouseButtonPressedImpl(int button) = 0;
	virtual float GetMouseXImpl() = 0;
	virtual float GetMouseYImpl() = 0;
	virtual std::pair<float, float> GetMousePositionImpl() = 0;
private:
	static Scope<Input> s_Instance;
};
}