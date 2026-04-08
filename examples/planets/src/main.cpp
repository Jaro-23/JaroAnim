#include <jaroAnim/core/animator.hpp>

using namespace JaroAnim;
using namespace JaroViewer;

int main(int argc, char* argv[]) {
	Animator animator{"JaroAnim demo"};
	JaroViewer::EngineState* state = animator.getState();

	// Create material and object
	ObjectManager& om   = state->objectManager;
	MaterialManager* mm = om.getMaterialManager();
	om.registerModel("backpack", "./examples/planets/models/backpack/backpack.obj", PredefinedShader::BASIC);

	// Add light
	Tools::LightColor lightColor{glm::vec3(0.05f), glm::vec3(0.55f), glm::vec3(1.00f)};
	std::shared_ptr<DirectionalLight> dir{
	  new DirectionalLight{glm::vec3(-0.2f, -1.0f, -0.3f), lightColor}
	};
	state->lights.addDirLight(dir);

	// Place a backpack
	Object obj = om.createObject("backpack");
	obj->setScale(0.1f);
	obj->setTranslation(glm::vec3(0.0f, 0.0f, -1.0f));

	glm::quat q = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)));
	animator.registerAnimation(
	  obj,
	  {Frame{.t = 0.0f, .position = glm::vec3(0.0f, 0.0f, -1.0f), .quaternion = q, .scale = glm::vec3(1.0f, 1.0f, 1.0f)},
	   Frame{.t = 6.0f, .position = glm::vec3(2.0f, 0.0f, -3.0f), .quaternion = q, .scale = glm::vec3(1.0f, 1.0f, 1.0f)},
	   Frame{.t = 12.0f, .position = glm::vec3(0.0f, 0.0f, -5.0f), .quaternion = q, .scale = glm::vec3(1.0f, 1.0f, 1.0f)},
	   Frame{.t = 18.0f, .position = glm::vec3(-2.0f, 0.0f, -5.0f), .quaternion = q, .scale = glm::vec3(1.0f, 1.0f, 1.0f)},
	   Frame{.t = 24.0f, .position = glm::vec3(0.0f, 0.0f, -1.0f), .quaternion = q, .scale = glm::vec3(1.0f, 1.0f, 1.0f)}}
	);

	animator.run();
	return 0;
}
