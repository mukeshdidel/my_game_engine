#pragma once


#include "Soul/Core.h"
#include "Soul/Events/Event.h"

namespace soul {
	class SOUL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName; // For debugging purposes because we dont need to use the name of the layer in the actual game, we just need it for debugging
	};
}