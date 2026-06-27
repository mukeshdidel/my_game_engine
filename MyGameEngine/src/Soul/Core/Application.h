#pragma once

#include "Soul/Events/ApplicationEvent.h"
#include "Soul/Core/Core.h"
#include "Soul/Events/Event.h"


#include "Soul/Core/LayerStack.h"
#include "Soul/Core/Window.h"

#include "Soul/ImGui/ImGuiLayer.h"

#include "Soul/Renderer/Buffer.h"
#include "Soul/Renderer/OrthographicCamera.h"
#include "Soul/Renderer/Shader.h"
#include "Soul/Renderer/VertexArray.h"


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
		void Close();

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		
		
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;		

	private:
		static Application* s_Instance ;
	};

	// To be defined in client
	Application* CreateApplication();
}


