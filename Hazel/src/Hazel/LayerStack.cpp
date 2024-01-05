#include "hzpch.h"
#include "LayerStack.h"
namespace Hazel {
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layer.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer * layer : m_Layer)
		{
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layer.emplace(m_LayerInsert, layer);
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layer.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layer.begin(), m_Layer.end(), layer);
		if (it !=m_Layer.end())
		{
			m_Layer.erase(it);
			m_LayerInsert--;
		}
	}
	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(m_Layer.begin(), m_Layer.end(), layer);
		if (it != m_Layer.end())
		{
			m_Layer.erase(it);
		}
	}
}
