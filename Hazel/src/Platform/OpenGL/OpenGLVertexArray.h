#pragma once
#include"Hazel/Renderer/VertexArray.h"

namespace Hazel {
	class OpenGLVertexArray:public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const Ref<VetexBuffer>& vertexBuffer) override;// 添加顶点缓冲对象
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;	// 设置索引缓冲对象，一般只有一个

		virtual const std::vector<Ref<VetexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers;};
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };

	private:
		uint32_t m_RendererID;

		std::vector<Ref<VetexBuffer>> m_VertexBuffers;// 拥有的顶点缓冲对象列表
		Ref<IndexBuffer> m_IndexBuffer;					// 拥有的索引缓冲对象

	};
}


