#pragma once
#include "Hazel/Renderer/RenderAPI.h"
namespace Hazel {
	class OpenGLRendererAPI:public RendererAPI
	{
	public:

		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const Ref<VertexArray>& indexBuffer) override;


	};
}