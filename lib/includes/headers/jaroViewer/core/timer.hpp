#pragma once

namespace JaroViewer {
	class Timer {
	public:
		Timer();
		float getDeltaTime();

	private:
		float mLastTime;
	};
} // namespace JaroViewer
