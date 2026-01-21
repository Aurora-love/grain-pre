#pragma once
#include "engine_services/renderer/RendererAPI.h"

namespace GE {
class OpenGLRendererAPI : public RendererAPI {
public:
	virtual void Init() override;

};
}
