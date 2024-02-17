#pragma once
#include "Core.h"
#include "Hazel/Core/TimeStep.h"
#include "Events/Event.h"
namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void DeAttach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}

