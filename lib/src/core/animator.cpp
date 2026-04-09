#include "jaroAnim/core/animator.hpp"
#include "jaroViewer/core/engine.hpp"
#include <algorithm>

using namespace JaroAnim;

Animator::Animator(const std::string& windowTitle, const std::string& cubemap)
  : mEngine(JaroViewer::EngineArgs{.windowTitle = windowTitle, .windowSamples = 16, .cubemapParams = cubemap}
    ) {
	mEngine.setUpdateFunc([this](float delta) { this->update(delta); });
}

void Animator::run() { mEngine.start(); }

JaroViewer::EngineState* Animator::getState() { return mEngine.getState(); }

void Animator::registerAnimation(JaroViewer::ObjectRef obj, const std::vector<Frame>& frames) {
	for (size_t i = 0; i < frames.size() - 1; ++i) {
		Path path = Path::line(frames.at(i).position, frames.at(i + 1).position);
		mTranslationAnimations.push_back(PathAnim{
		  .path      = path,
		  .obj       = obj,
		  .speedFunc = frames.at(i).speedFunc,
		  .startTime = frames.at(i).t,
		  .duration  = frames.at(i + 1).t - frames.at(i).t,
		});
		// TODO: Handle rotation and scale
	}
}

void Animator::update(float delta) {
	mCurrentTime += delta;
	for (auto& anim : mTranslationAnimations) {
		if (anim.obj.expired()) continue;
		if (mCurrentTime < anim.startTime || anim.startTime + anim.duration < mCurrentTime)
			continue;

		float t                = (mCurrentTime - anim.startTime) / anim.duration;
		t                      = std::clamp(anim.speedFunc(t), 0.0f, 1.0f);
		glm::vec3 pos          = anim.path.distInterpolate(t);
		JaroViewer::Object obj = anim.obj.lock();
		obj->setTranslation(pos);
	}
}
