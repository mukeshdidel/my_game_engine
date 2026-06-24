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
	SL_PROFILE_FUNCTION();

	m_DrogbaTexture = soul::Texture2D::Create("assets/textures/drogba.jpg");
	m_SpriteSheet = soul::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStairs = soul::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	
}

void Sandbox2D::OnDetach()
{
	SL_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(soul::TimeStep ts)
{
	
	SL_PROFILE_FUNCTION();

	
	m_CameraController.OnUpdate(ts);

	soul::Renderer2D::ResetStats();

	soul::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	soul::RenderCommand::Clear();

	//soul::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//soul::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.0f, 0.0f, 1.0f, 1.0f});
	//soul::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 0.5f }, m_SquareColor);
	//soul::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 2.0f, 2.0f }, m_DrogbaTexture, 1.0f);
	//soul::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f }, { 2.0f, 2.0f }, 45.0f, m_DrogbaTexture, 10.0f);


	//soul::Renderer2D::EndScene();


	soul::Renderer2D::BeginScene(m_CameraController.GetCamera());

	soul::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureStairs);

	soul::Renderer2D::EndScene();
	

}

void Sandbox2D::OnImGuiRender()
{

	SL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = soul::Renderer2D::GetStats();
	ImGui::Text("Renderer2D stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());  


	ImGui::ColorEdit3("square color", glm::value_ptr(m_SquareColor));


	ImGui::End();
}

void Sandbox2D::OnEvent(soul::Event& event)
{
	m_CameraController.OnEvent(event);
}
