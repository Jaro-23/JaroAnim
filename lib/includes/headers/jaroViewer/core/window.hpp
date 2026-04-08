#pragma once

#include <glm/glm.hpp>
#include <string>
#include <sys/types.h>

struct GLFWwindow;

namespace JaroViewer {
	struct Size {
		int width;
		int height;
	};

	class Window {
	public:
		Window(int major, int minor, int width, int height, const std::string& title);
		Window(int major, int minor, int width, int height, const std::string& title, uint samples);

		Window(Window&& other) noexcept;
		Window(const Window&)            = delete;
		Window& operator=(const Window&) = delete;

		~Window();

		// Basic operations
		void clear();
		void update();
		bool updateView();
		void toggleFullscreen();
		void setShouldClose(bool close);
		void setMouseMode(uint mode);
		void makeActive();
		bool insideScreen(int x, int y) const;

		// getters
		bool shouldClose() const;
		int getMouseMode() const;
		Size getSize() const;
		GLFWwindow* cPtr() const;
		glm::mat4 getProjection() const;

	private:
		GLFWwindow* mWindow;
		int mWidth, mHeight;
		int mWindowedWidth, mWindowedHeight;
		int mPosX, mPosY;
		uint mSamples = 1;
		bool mIsFullscreen;
	};
} // namespace JaroViewer
