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
	m_SpriteSheet = soul::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");


	m_TexStairs = soul::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 0, 11 }, { 128, 128 });
	m_TexStairs = soul::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 256 }, {1, 2});

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth; 

	s_TextureMap['D'] = soul::SubTexture2D::CreateFromCoords(m_SpriteSheet, {6, 11}, {128, 128});
	s_TextureMap['W'] = soul::SubTexture2D::CreateFromCoords(m_SpriteSheet, {11, 11}, {128, 128});


	m_CameraController.SetZoomLevel(5.0f);
	
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

	for (uint32_t y = 0; y < m_MapHeight; y++) {
		for (uint32_t x = 0; x < m_MapWidth; x++) {
			char tileType = s_MapTiles[x + y * m_MapWidth];
			soul::Ref<soul::SubTexture2D> texture;

			if (s_TextureMap.find(tileType) != s_TextureMap.end()) {
				texture = s_TextureMap[tileType];
			}
			else {
				texture = m_TexTree;
			}

			soul::Renderer2D::DrawQuad({ x - m_MapWidth/2.0f, y -m_MapHeight /2.0f, 0.5f }, { 1.0f,1.0f }, texture);
		}
	}

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
