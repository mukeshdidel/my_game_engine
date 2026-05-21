#pragma once

#include "Soul/Core/Core.h"

namespace soul {

	class SOUL_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) {return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { auto [x, y] = GetMousePosition(); return x; }
		inline static float GetMouseY() { auto [x, y] = GetMousePosition(); return y; }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private: 
		static Input* s_Instance;
	};
}