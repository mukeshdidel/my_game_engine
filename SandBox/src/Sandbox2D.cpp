#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Timer {
public:
	Timer(const char* name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!m_Stopped) 
			Stop();
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();
		
		m_Stopped = true;

		float duration = (end - start);
		SL_CORE_INFO("{0}: {1}ms", m_Name, duration);
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	bool m_Stopped;
};


Sandbox2D::Sandbox2D()
	: Layer("sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_DrogbaTexture = soul::Texture2D::Create("assets/textures/drogba.jpg");

	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(soul::TimeStep ts)
{
	m_CameraController.OnUpdate(ts);

	soul::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	soul::RenderCommand::Clear();

	soul::Renderer2D::BeginScene(m_CameraController.GetCamera());

	soul::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.0f, 0.0f, 1.0f, 1.0f});
	soul::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 0.5f }, m_SquareColor);
	soul::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 10.0f, 10.0f }, m_DrogbaTexture);


	soul::Renderer2D::EndScene();
	

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(soul::Event& event)
{
	m_CameraController.OnEvent(event);
}
