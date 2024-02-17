#include"hzpch.h"
#include <glad/glad.h>
#include "Application.h"
#include "Log.h"
//#include <GLFW/glfw3.h>

#include "Hazel/Core/TimeStep.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/Input.h"

#include "Renderer/Renderer.h"


#include <GLFW/glfw3.h>





namespace Hazel{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance,"Application Already Exists")
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);

		//Vertex Array 
		//Vertex Buffer
		//Index Buffer
		//Shader
		

	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		while (m_Running) {
			// 计算两帧间隔时间
			float time = (float)glfwGetTime();	// 是从应用开始计算总共的时间
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
		

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		};

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

		/*HZ_CORE_INFO(e.ToString());*/

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowCloseEvent(Event& e)
	{
		m_Running = false;
		return true;
	}

}

