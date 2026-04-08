#pragma once

#include "jaroViewer/core/window.hpp"

#include <functional>
#include <map>
#include <vector>

namespace JaroViewer {
	struct InputParams {
		float deltaTime;
		bool mouseInScreen;
		int mouseX, mouseY;
	};

	class InputHandler {
	public:
		enum class KeyAction { DOWN, UP, PRESS, RELEASE };

		InputHandler(Window* window);
		Window* getWindow() const;
		void addKey(int key, KeyAction action, std::function<void(InputParams)> func);
		void addMouseKey(int key, KeyAction action, std::function<void(InputParams)> func);
		void addMouseMoveEvent(std::function<void(GLFWwindow*, double, double)> func);
		void processInputs(float deltaTime);

	private:
		void addMouseCallback();

		struct KeyState {
			std::function<void(InputParams)> function;
			bool isPressed;
			KeyAction action;
			bool isKey;
		};

		Window* mWindow;
		std::map<int, KeyState> mKeys;
		std::vector<std::function<void(GLFWwindow*, double, double)>> mMouseMoveEvents;
	};
} // namespace JaroViewer
