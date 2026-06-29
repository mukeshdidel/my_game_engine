#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24;

static const char* s_MapTiles = 
"WWWWWWWWWDDDDDDDDWWWWWWW"
"WWWWWDDDDDDDDDDDDDWWWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWDDDDDDDDDDDDDDDDDWWW"
"WWDDDDDDDDDWDDDDDDDDDDWW"
"WWDDDDDDDDWWWDDDDDDDDDWW"
"WWDDDDDDDWWWWWDDDDDDDWWW"
"WWWWDDDDDDWWWWDDDDDWWWWW"
"WWWWWWWDDDDWWDDDDDDWWWWW"
"WWWWWWWWWWDDDDWWWWWWWWWW"
"WWWWWWWWWWWWDDDDWWWWWWWW"
"WWWWWWWWWWDDDDDDWWWWWWWW"
"WWWWWWWWWWWWDDDWWWWWWWWW"
"WWWWWWWWWWWWWDWWWWWWWWWW"
	;


Sandbox2D::Sandbox2D()
	: Layer("sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	SL_PROFILE_FUNCTION();

	m_DrogbaTexture = soul::Texture2D::Create("assets/textures/drogba.jpg");
	
	

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

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		SL_PROFILE_SCOPE("Renderer Draw");
		soul::Renderer2D::BeginScene(m_CameraController.GetCamera());
		soul::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		soul::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		soul::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		soul::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_DrogbaTexture, 10.0f);
		soul::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_DrogbaTexture, 20.0f);
		soul::Renderer2D::EndScene();

		soul::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				soul::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		soul::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	SL_PROFILE_FUNCTION();

	
		ImGui::Begin("Settings");

		auto stats = soul::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	
}

void Sandbox2D::OnEvent(soul::Event& event)
{
	m_CameraController.OnEvent(event);
}
