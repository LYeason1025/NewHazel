#pragma once
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class OpenGLVertexBuffer:public VetexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size, float* indices);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind()  const override;
		virtual void Unbind()  const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };


	private:
		uint32_t m_RenderID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t size, uint32_t* indices);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()  const;
		virtual void Unbind()  const;

		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RenderID;
		uint32_t m_Count;

	};
}