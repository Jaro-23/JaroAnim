#include "jaroAnim/deformation/ffd.hpp"
#include "glm/fwd.hpp"
#include "jaroViewer/geometry/basicShapes.hpp"
#include "jaroViewer/modifiers/modifier.hpp"
#include "jaroViewer/scene/object.hpp"
#include "jaroViewer/scene/objectManager.hpp"
#include <cassert>
#include <limits>

using namespace JaroAnim;

std::string FFD::getCode() {
	return "vec3 outVec = inVec;\n outVec.y += "
	       "sin(inVec.x * 100.0) * 0.2;\n return outVec;\n";
}

FFD::FFD(JaroViewer::ObjectManager* objectMan, size_t xSize, size_t ySize, size_t zSize)
  : mObjectMan(objectMan), mXSize(xSize), mYSize(ySize), mZSize(zSize) {
	mObjectMan->registerModel("ffdPoint", JaroViewer::cubeVertices, JaroViewer::PredefinedShader::WHITE, 0);
}

JaroViewer::ModifierParams FFD::getParams() const {
	assert(FFD::mRegistered && "Should be registered before use of params");

	JaroViewer::ModifierParams params{(float)FFD::mIdent, (float)mXSize, (float)mYSize, (float)mZSize};
	params.reserve(4 + mPoints.size() * 3); // 4 = size of predefined params

	for (const auto& obj : mPoints) {
		const glm::vec3 pos = obj->getPosition();
		params.push_back(pos.x);
		params.push_back(pos.y);
		params.push_back(pos.z);
	}

	return params;
}

void FFD::updateData(JaroViewer::ObjectData inputData) {
	mInputData  = inputData;
	mOutputData = inputData;
	resetPoints(); // TODO: Is this the best option? Probably not but what is alternative
}

void FFD::resetPoints() {
	size_t size = mXSize * mYSize * mZSize;
	mPoints.clear();
	mPoints.reserve(size);

	glm::vec3 minP  = mInputData.minPoint;
	glm::vec3 maxP  = mInputData.maxPoint;
	glm::vec3 range = maxP - minP;
	for (size_t i = 0; i < size; ++i) {
		JaroViewer::Object obj = mObjectMan->createObject("ffdPoint");

		obj->addListener([this](JaroViewer::RawObject*, JaroViewer::ObjectEvent event) {
			if (event != JaroViewer::ObjectEvent::TRANSFORM) return;
			glm::vec3 minPoint = glm::vec3(std::numeric_limits<float>().max());
			glm::vec3 maxPoint = glm::vec3(std::numeric_limits<float>().lowest());
			for (auto& obj : this->mPoints) {
				minPoint = glm::min(minPoint, obj->getPosition());
				minPoint = glm::max(minPoint, obj->getPosition());
			}

			bool changed = (minPoint != this->mOutputData.minPoint) ||
			  (maxPoint != this->mOutputData.maxPoint);
			this->mOutputData.minPoint = minPoint;
			this->mOutputData.maxPoint = maxPoint;
			if (changed) this->send(this, JaroViewer::ModifierEvent::OUTPUT_CHANGE);
		});

		float x = i % mXSize;
		float y = (i / mXSize) % mYSize;
		float z = i / (mXSize * mYSize);

		obj->setTranslation(glm::vec3(
		  minP.x + (range.x) * (x / (float)(mXSize - 1)),
		  minP.y + (range.y) * (y / (float)(mYSize - 1)),
		  minP.z + (range.z) * (z / (float)(mZSize - 1))
		));

		mPoints.push_back(obj);
	}
}
