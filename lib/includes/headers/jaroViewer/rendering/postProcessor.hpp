#pragma once

#include "jaroViewer/core/window.hpp"
#include "jaroViewer/graphics/frameBuffer.hpp"
#include "jaroViewer/rendering/shader.hpp"

#include <memory>
#include <string>

namespace JaroViewer {
	class PostProcessor {
	public:
		PostProcessor(Window* window, const std::string fragmentFile);
		void setupVao();

		void bindAndClear(float r, float g, float b, float a) const;
		void unbind() const;
		void render() const;
		void resize(uint width, uint height);

	private:
		std::unique_ptr<Shader> mShader;
		FrameBuffer mFrameBuffer;
		unsigned int mVaoBuffer;
	};
} // namespace JaroViewer
