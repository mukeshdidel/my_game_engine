#pragma once

#include "Soul/Layer.h"

#include "Soul/Events/ApplicationEvent.h"
#include "Soul/Events/KeyEvent.h"
#include "Soul/Events/MouseEvent.h"

namespace soul {
	class SOUL_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	private:
		float m_Time = 0.0f;
	};
}