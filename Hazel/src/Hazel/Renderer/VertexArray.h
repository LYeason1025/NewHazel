#pragma once
#include"Hazel/Renderer/Buffer.h"


namespace Hazel {
	class VertexArray
	{
	public:

		virtual ~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Ref<VetexBuffer>& vertexBuffer) = 0;// 添加顶点缓冲对象
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;	// 设置索引缓冲对象，一般只有一个
		virtual const std::vector<Ref<VetexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		static VertexArray* Create();// 基类指针指向子类对象
	
	private:
	};


}


