#pragma once
#include "Soul.h"

class Sandbox2D : public soul::Layer
{
public:

	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(soul::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(soul::Event& event) override;

private:
	soul::OrthographicCameraController m_CameraController;


	// Temp
	soul::Ref<soul::VertexArray> m_SquareVA;
	soul::Ref<soul::Shader> m_FlatColorShader;

	soul::Ref<soul::Texture> m_DrogbaTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0 };
};