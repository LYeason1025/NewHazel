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

		//����ʱ��ȡOpenGL������ַ�����䱣���ں���ָ���й��Ժ�ʹ��
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "��ʼ��Gladʧ��");
		//����OPENGL����

	
		/*HZ_CORE_INFO("OpenGL Renderer :{0},{1}",glGetString(GL_VENDOR),glGetString(GL_RENDER));*/


	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}
