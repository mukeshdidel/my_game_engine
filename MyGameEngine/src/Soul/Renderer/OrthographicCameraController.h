#pragma once

#include "Soul/Renderer/OrthographicCamera.h"
#include "Soul/Core/TimeStep.h"

#include "Soul/Events/MouseEvent.h"
#include "Soul/Events/ApplicationEvent.h"
#include "Soul/Events/KeyEvent.h"


namespace soul {

	struct OrthographicCameraBounds {
		float left, right, top, bottom;
		float GetWidth() { return right - left; }
		float GetHeight() { return top - bottom; }
	};

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }


		void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }
		float GetZoomLevel() const { return m_ZoomLevel;  }

		const OrthographicCameraBounds& GetBounds() { return m_Bounds; }
	private:

		void CalculateView();


		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		OrthographicCameraBounds m_Bounds;

		bool m_Rotation;  

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;

		


	};
}


