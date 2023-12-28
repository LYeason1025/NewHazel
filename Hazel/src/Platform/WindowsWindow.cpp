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
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");// 是Core.h里面预处理器指令定义了HZ_CORE_ASSERT
			s_GLFWInitialized = true;
		}
		// 创建窗口//
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		// 设置glfw当前的上下文
		glfwMakeContextCurrent(m_Window);
		/*
			设置窗口关联的用户数据指针。这里GLFW仅做存储，不做任何的特殊处理和应用。
			window表示操作的窗口句柄。
			pointer表示用户数据指针。
		*/
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


		//--设置glfw事件回调
	}
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}


