#include "hzpch.h"
#include "VertexArray.h"
#include"Platform/OpenGL/OpenGLVertexArray.h"
#include"Hazel/Renderer/Renderer.h"

namespace Hazel {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supportde");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		default:
			break;
		}

		HZ_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}
