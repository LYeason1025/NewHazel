#include <Hazel.h>

#include"Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer :public Hazel::Layer {
public:
	ExampleLayer():
		Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) , m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_SquarePosition(0.0f)
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
			/*	 0.0f, -0.5f, 0.0f,*/
		};

		uint32_t indices[3] = { 0,1,2 };
		m_VertexArray.reset(Hazel::VertexArray::Create());

		Hazel::Ref<Hazel::VetexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VetexBuffer::Create(sizeof(vertices), vertices));

		Hazel::BufferLayout layout = {//BufferLayout是顶点缓冲布局类
		{ Hazel::ShaderDataType::Float3, "a_Position" },// 一个元素是BufferElement类
		{ Hazel::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);//  顶点缓冲布局类与顶点缓冲交互
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(sizeof(indices) / sizeof(uint32_t), indices));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;


			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset( Hazel::Shader::Create(vertexSrc, fragmentSrc));


		//
		float vertices2[3 * 4] = {
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
		   -0.5f,  0.5f, 0.0f
		};

		uint32_t SqaureIndices[6] = { 0,1,2,2,3,0 };
		m_SqaureVertexArray.reset(Hazel::VertexArray::Create());

		Hazel::Ref<Hazel::VetexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Hazel::VetexBuffer::Create(sizeof(vertices2), vertices2));

		Hazel::BufferLayout layout2 = {//BufferLayout是顶点缓冲布局类
		{ Hazel::ShaderDataType::Float3, "a_Position" },// 一个元素是BufferElement类
		};
		squareVertexBuffer->SetLayout(layout2);//  顶点缓冲布局类与顶点缓冲交互

		m_SqaureVertexArray->AddVertexBuffer(squareVertexBuffer);

		Hazel::Ref<Hazel::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Hazel::IndexBuffer::Create(sizeof(SqaureIndices) / sizeof(uint32_t), SqaureIndices));

		m_SqaureVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position =u_ViewProjection *  u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_color;
			void main()
			{
				color = vec4(u_color,1.0f);
			}
		)";
		m_SquareShader.reset(Hazel::Shader::Create(vertexSrc2, fragmentSrc2));

	}
	void OnUpdate(Hazel::Timestep ts) override {

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();


		if (Hazel::Input::IsKeyPressed(Hazel::Key::Right))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed*ts;
		}
		if (Hazel::Input::IsKeyPressed(Hazel::Key::Left))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(Hazel::Key::A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(Hazel::Key::D))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}



		if (Hazel::Input::IsKeyPressed(Hazel::Key::L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(Hazel::Key::J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}

		if (Hazel::Input::IsKeyPressed(Hazel::Key::I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(Hazel::Key::K)) 
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		
		Hazel::Renderer::BeginScene(m_Camera);
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.8f, 0.2f, 0.3f, 1.0f);


		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_color", m_SquareColor);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));



		for (int i = 0; i < 20; i++) 
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(j * 0.11f, i * 0.11f, 0.0f);
				glm::mat4 Transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazel::Renderer::Submit(m_SqaureVertexArray, m_SquareShader, Transform);
			}	
		}

			
		Hazel::Renderer::Submit(m_VertexArray, m_Shader);

		Hazel::Renderer::EndScene();
	}
	void OnEvent(Hazel::Event& event) override {  }


	virtual void OnImGuiRender() override{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
private:

	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_SquareShader;
	Hazel::Ref<Hazel::VertexArray> m_SqaureVertexArray;

	Hazel::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 30.0F;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed=1.0f;

	glm::vec3 m_SquareColor = {0.2f,0.3f,0.7f};

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	};
	~Sandbox() {};
};


Hazel::Application* Hazel::CreateApplication() {

	return new Sandbox();
}


