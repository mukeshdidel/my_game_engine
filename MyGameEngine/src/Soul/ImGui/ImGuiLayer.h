#pragma once

#include "Soul/Core/Layer.h"

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
		void OnImGuiRender() override;

		void Begin();
		void End();	

	private:
		float m_Time = 0.0f;
	};
}