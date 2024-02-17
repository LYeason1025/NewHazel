#pragma once

#include "Core.h"
#include "Layer.h"


#include<vector>
namespace Hazel{

	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layer.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layer.end(); }

	private:
		std::vector<Layer*> m_Layer;
		unsigned int m_LayerInsertIndex = 0;
	};

}

