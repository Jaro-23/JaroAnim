#pragma once

#include <sys/types.h>
#include <vector>

namespace JaroViewer {
	class GpuVector {
	public:
		GpuVector();

		size_t count() const;
		size_t size() const;
		void load(uint position) const;

		void copy(const std::vector<float>& data, size_t offset);
		void move(size_t from, size_t to);
		void move(size_t from, size_t to, size_t count);

	private:
		void enlarge(float factor = 2.0);
		void copy(uint fromBuffer, uint toBuffer);
		void genDataTex(uint* tex, uint* tbo, size_t size);

		size_t mCount;
		uint mTexture;
		uint mBuffer;
	};
} // namespace JaroViewer
