#pragma once

#include "jaroViewer/core/window.hpp"
#include "jaroViewer/graphics/cubemap.hpp"
#include "jaroViewer/input/inputHandler.hpp"
#include "jaroViewer/lighting/lightSet.hpp"
#include "jaroViewer/rendering/postProcessor.hpp"
#include "jaroViewer/rendering/uniformBuffer.hpp"
#include "jaroViewer/scene/camera.hpp"
#include "jaroViewer/scene/objectManager.hpp"

#include <glm/glm.hpp>
#include <optional>
#include <string>

namespace JaroViewer {
	struct EngineArgs {
		// Window args
		int openGLMajor               = 4;
		int openGLMinor               = 6;
		int windowWidth               = 600;
		int windowHeight              = 450;
		std::string windowTitle       = "Basic window";
		uint windowSamples            = 1;
		std::string postProcessShader = "";
		std::variant<std::string, std::vector<std::string>> cubemapParams = "";
	};

	struct EngineState {
		Window window;
		Camera camera;
		InputHandler input;
		ObjectManager objectManager;
		LightSet lights;
		std::optional<Cubemap> cubemap;
		std::optional<PostProcessor> postProcessor;

		EngineState(Window&& w, Camera c, std::optional<Cubemap> cm, std::optional<PostProcessor> pp)
		  : window(std::move(w)),
		    camera(std::move(c)),
		    input(&this->window),
		    objectManager(),
		    lights(),
		    cubemap(std::move(cm)),
		    postProcessor(std::move(pp)) {}
	};

	class Engine {
	public:
		static EngineState argsToState(const EngineArgs& args);
		Engine(const EngineArgs& args);
		~Engine();

		void start();
		EngineState* getState();
		void triggerClick(InputHandler::KeyAction action, InputParams params);

		void setUpdateFunc(std::function<void(float delta)> func);

		std::function<void(InputHandler::KeyAction action, Object obj)> mClickCallback;

	private:
		struct Tranformation {
			glm::mat4 projection;
			glm::mat4 view;
		};

		void render();

		EngineState mState;
		std::shared_ptr<UniformBuffer> mTransformUBO;
		std::shared_ptr<UniformBuffer> mLightsUBO;

		std::function<void(float delta)> mUpdateFunc;
	};
} // namespace JaroViewer
