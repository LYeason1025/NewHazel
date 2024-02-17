#pragma once
#include"Hazel/Renderer/Buffer.h"


namespace Hazel {
	class VertexArray
	{
	public:

		virtual ~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VetexBuffer>& vertexBuffer) = 0;// ��Ӷ��㻺�����
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;	// ���������������һ��ֻ��һ��
		virtual const std::vector<Ref<VetexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		static VertexArray* Create();// ����ָ��ָ���������
	
	private:
	};


}


