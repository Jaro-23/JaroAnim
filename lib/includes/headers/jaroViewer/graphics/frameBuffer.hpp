#pragma once

#include <sys/types.h>

namespace JaroViewer {
	struct FrameBufferArgs {
		int width;
		int height;
		bool readableColor;
		bool readableDepthStencil;
		uint formatType;
	};

	class FrameBuffer {
	public:
		FrameBuffer(const FrameBufferArgs& args);
		~FrameBuffer();

		void bind() const;
		void unbind() const;

		void resize(uint width, uint height);
		void clear(float r, float g, float b, float a) const;

		uint getColor() const;
		uint getDepthStencil() const;

	private:
		void genBuffer();
		uint genTexure(uint formatType);
		uint genRenderBuffer(uint formatType);
		uint bindTexture(uint usage, uint formatType);
		uint bindRenderBuffer(uint usage);
		void createStorage(bool readable, uint* textureStorage, uint* renderStorage, uint usage, uint formatType);

		uint mID;
		uint mColorTexture;
		uint mDepthStencilTexture;
		uint mColorRBO;
		uint mDepthStencilRBO;

		int mWidth;
		int mHeight;
		bool mReadableColor;
		bool mReadableDepthStencil;
		uint mFormatType;
	};
} // namespace JaroViewer
