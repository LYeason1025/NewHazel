#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Log.h"

static bool s_GLFWInitialized = false;
namespace Hazel {
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Data.VSync = enabled;
		
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");// ��Core.h����Ԥ������ָ�����HZ_CORE_ASSERT
			s_GLFWInitialized = true;
		}
		// ��������//
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		// ����glfw��ǰ��������
		glfwMakeContextCurrent(m_Window);
		/*
			���ô��ڹ������û�����ָ�롣����GLFW�����洢�������κε����⴦���Ӧ�á�
			window��ʾ�����Ĵ��ھ����
			pointer��ʾ�û�����ָ�롣
		*/
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		//--����glfw�¼��ص�
	}
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}


