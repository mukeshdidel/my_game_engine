#pragma once
#include "Soul.h"

namespace soul {


	class EditorLayer : public Layer
	{
	public:

		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(TimeStep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_CameraController;
		Ref<FrameBuffer> m_FrameBuffer;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;

		Ref<Texture2D> m_DrogbaTexture;
		Ref<Texture2D> m_SpriteSheet;

		Ref<SubTexture2D> m_TexStairs;
		Ref<SubTexture2D> m_TexDurt;
		Ref<SubTexture2D> m_TexTree;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };



		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0 };

		uint32_t m_MapWidth, m_MapHeight;
		std::unordered_map<char, Ref<SubTexture2D>> s_TextureMap;



	};

}