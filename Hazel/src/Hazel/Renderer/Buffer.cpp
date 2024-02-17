#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel {

	VetexBuffer* VetexBuffer::Create(uint32_t size, float* vertices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supportde");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(size, vertices);
		default:
			break;
		}

		HZ_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t size, uint32_t* indices)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supportde");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(size, indices);
		default:
			break;
		}

		HZ_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

}