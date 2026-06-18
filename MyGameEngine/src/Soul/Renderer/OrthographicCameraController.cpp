#include "soulpch.h"
#include "OrthographicCameraController.h"
#include "Soul/Core/Input.h"
#include "Soul/Core/KeyCode.h"

namespace soul {



	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		SL_PROFILE_FUNCTION();


		if (soul::Input::IsKeyPressed(SL_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		if (soul::Input::IsKeyPressed(SL_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (soul::Input::IsKeyPressed(SL_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation) {

			if (soul::Input::IsKeyPressed(SL_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (soul::Input::IsKeyPressed(SL_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);

		}


		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		SL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		SL_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		SL_PROFILE_FUNCTION();

		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

}