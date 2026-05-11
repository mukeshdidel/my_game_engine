#pragma once

#include "Core.h"
#include "Soul/Events/Event.h"
#include "Soul/Events/ApplicationEvent.h"
#include "Soul/Window.h"
#include "Soul/LayerStack.h"


namespace soul {

	class SOUL_API Application
	{
	public: 
		Application();
		virtual~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();
}


