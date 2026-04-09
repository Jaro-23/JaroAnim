#include "jaroAnim/interpolation/path.hpp"

#include <glm/glm.hpp>
#include <jaroViewer/core/engine.hpp>
#include <vector>

namespace JaroAnim {
	struct Frame {
		float t;
		glm::vec3 position;
		glm::quat quaternion;
		glm::vec3 scale;
		std::function<float(float)> speedFunc = [](float t) { return t; };
	};

	class Animator {
	public:
		Animator(const std::string& windowTitle, const std::string& cubemap);
		void run();

		JaroViewer::EngineState* getState();
		void registerAnimation(JaroViewer::Object obj, const std::vector<Frame>& frames);

	private:
		void update(float delta);

		struct PathAnim {
			Path path;
			JaroViewer::Object obj;
			std::function<float(float)> speedFunc;
			float startTime;
			float duration;
		};

		JaroViewer::Engine mEngine;
		float mCurrentTime;
		std::vector<PathAnim> mTranslationAnimations;
	};
} // namespace JaroAnim
