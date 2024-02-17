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
		virtual void AddVertexBuffer(const Ref<VetexBuffer>& vertexBuffer) override;// ��Ӷ��㻺�����
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;	// ���������������һ��ֻ��һ��

		virtual const std::vector<Ref<VetexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers;};
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };

	private:
		uint32_t m_RendererID;

		std::vector<Ref<VetexBuffer>> m_VertexBuffers;// ӵ�еĶ��㻺������б�
		Ref<IndexBuffer> m_IndexBuffer;					// ӵ�е������������

	};
}


