#pragma once

#include "Core.h"
#include "Soul/Events/Event.h"
#include "Soul/Events/ApplicationEvent.h"
#include "Soul/Window.h"
#include "Soul/LayerStack.h"

#include "Soul/ImGui/ImGuiLayer.h"
#include "Soul/Renderer/Shader.h"

#include "Soul/Renderer/Buffer.h"

#include "Soul/Renderer/VertexArray.h"

#include "Soul/Renderer/OrthographicCamera.h"


namespace soul {

	class Application
	{
	public: 
		Application();
		virtual~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		
		LayerStack m_LayerStack;


		float m_LastFrameTime = 0.0f; 

		bool m_Minimized = false;



		

	private:
		static Application* s_Instance ;
	};

	// To be defined in client
	Application* CreateApplication();
}


