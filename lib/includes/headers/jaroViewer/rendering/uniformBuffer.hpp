#pragma once

#include <sys/types.h>

namespace JaroViewer {
	class UniformBuffer {
	public:
		UniformBuffer(uint position, uint size, uint usage);
		void updateData(const void* data);

	private:
		uint mSize;
		uint mID;
	};
} // namespace JaroViewer
