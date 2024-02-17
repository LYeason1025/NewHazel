#include "hzpch.h"
#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <Hazel/Log.h>
#include "Renderer.h"
#include "glm/gtc/type_ptr.hpp"

namespace Hazel {


	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supportde");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc,fragmentSrc);
		default:
			break;
		}

		HZ_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
	

	
}