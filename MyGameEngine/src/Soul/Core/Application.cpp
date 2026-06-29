#include "soulpch.h"
#include "Application.h"

#include "Soul/Core/Log.h"
#include "Soul/Core/Input.h"
#include "Soul/Core/TimeStep.h"

#include "Soul/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace soul {


	Application* Application::s_Instance = nullptr;


	Application::Application(const std::string& name)
	{

		SL_PROFILE_FUNCTION();

		SL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create(WindowProps(name)));
		m_Window->SetEventCallback(SL_BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		SL_PROFILE_FUNCTION();

		while (m_Running) {

			float time = glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					SL_PROFILE_SCOPE("LayerStack OnUpdate - Application::Run");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timeStep);
				}
				m_ImGuiLayer->Begin();
				{
					SL_PROFILE_SCOPE("LayerStack OnImGuiRender - Application::Run");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();

			}
			//SL_CORE_TRACE("{0}, {1}", Input::GetMouseX(), Input::GetMouseY());

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}


	void Application::OnEvent(Event& e)
	{
		SL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SL_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SL_BIND_EVENT_FN(OnWindowResize));

		//SL_CORE_INFO("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		SL_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		SL_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{

		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		SL_PROFILE_FUNCTION();

		if (e.GetHeight() == 0 || e.GetWidth() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());


		return false;
	}
}