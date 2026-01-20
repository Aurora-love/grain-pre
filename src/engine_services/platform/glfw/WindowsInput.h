#pragma once
#include "engine_services/core/Input.h"

namespace GE {

class WindowsInput : public Input {
protected:
    virtual bool IsKeyPressedImpl(uint32_t keycode) override;
	virtual bool IsMouseButtonPressedImpl(int button) override;
	virtual float GetMouseXImpl() override;
	virtual float GetMouseYImpl() override;
	virtual std::pair<float, float> GetMousePositionImpl() override;
};
}