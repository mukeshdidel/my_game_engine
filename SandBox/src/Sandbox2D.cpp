#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>


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
	
	SL_PROFILE_FUNCTION();

	{
		SL_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);

	}


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

	SL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit3("square color", glm::value_ptr(m_SquareColor));


	ImGui::End();
}

void Sandbox2D::OnEvent(soul::Event& event)
{
	m_CameraController.OnEvent(event);
}
