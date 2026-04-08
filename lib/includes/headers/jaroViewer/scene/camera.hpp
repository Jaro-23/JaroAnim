#pragma once

#include "jaroViewer/input/inputHandler.hpp"
#include "jaroViewer/lighting/spotlight.hpp"
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <memory>

namespace JaroViewer {
	class Camera {
	public:
		Camera(glm::vec3 pos, glm::vec3 up);
		void setFlashlight(const std::shared_ptr<JaroViewer::Spotlight> flashlight);
		void toggleFlashlight();
		void addControls(InputHandler& handler);

		void goForward(float deltaTime);
		void goRight(float deltaTime);
		void updateDirection(float yaw, float pitch);

		glm::mat4 getView() const;
		glm::vec3 getPosition() const;
		void setSpeed(float speed);

	private:
		bool getFirstMove() const;
		void setFirstMove(bool state);

		float getMouseX() const;
		float getMouseY() const;
		void setMouseX(float x);
		void setMouseY(float y);

		float getSensitivity() const;
		std::function<void(GLFWwindow*, double, double)> getMouseEvent();

		std::shared_ptr<JaroViewer::Spotlight> mFlashlight;
		bool mEnableFlashlight;

		// Lateral freedom
		glm::vec3 mPos;
		glm::vec3 mFront;
		glm::vec3 mUp;

		float mSpeed = 1.0f;

		// Rotational freedom
		float mYaw   = -90.0f;
		float mPitch = 0.0f;

		float mMouseX   = 0.0f;
		float mMouseY   = 0.0f;
		bool mFirstMove = true;

		float mSensitivity = 0.07f;
	};
} // namespace JaroViewer
