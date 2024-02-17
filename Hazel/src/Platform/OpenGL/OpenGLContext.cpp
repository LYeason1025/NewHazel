#include "hzpch.h"
#include "OpenGLContext.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <Hazel/Core.h>


namespace Hazel {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle,"Handle is null")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);

		//运行时获取OpenGL函数地址并将其保存在函数指针中供以后使用
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "初始化Glad失败");
		//测试OPENGL函数

	
		/*HZ_CORE_INFO("OpenGL Renderer :{0},{1}",glGetString(GL_VENDOR),glGetString(GL_RENDER));*/


	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}
