#include "jaroAnim/deformation/ffd.hpp"
#include "glm/fwd.hpp"
#include "jaroViewer/geometry/basicShapes.hpp"
#include "jaroViewer/modifiers/modifier.hpp"
#include "jaroViewer/scene/object.hpp"
#include "jaroViewer/scene/objectManager.hpp"
#include <cassert>
#include <iostream>
#include <limits>

using namespace JaroAnim;

std::string FFD::getCode() {
	return "float x = getDataFromVector(modifierData, modifierIndex);\n"
	       "float y = getDataFromVector(modifierData, modifierIndex + 1);\n"
	       "float z = getDataFromVector(modifierData, modifierIndex + 2);\n"
	       "vec3 minP = vec3(x,y,z);\n"
	       "modifierIndex += 3;\n"

	       "x = getDataFromVector(modifierData, modifierIndex);\n"
	       "y = getDataFromVector(modifierData, modifierIndex + 1);\n"
	       "z = getDataFromVector(modifierData, modifierIndex + 2);\n"
	       "vec3 maxP = vec3(x,y,z);\n"
	       "modifierIndex += 3;\n"

	       "int xSize = int(getDataFromVector(modifierData, modifierIndex));\n"
	       "int ySize = int(getDataFromVector(modifierData, modifierIndex + "
	       "1));\n"
	       "int zSize = int(getDataFromVector(modifierData, modifierIndex + "
	       "2));\n"
	       "modifierIndex += 3;\n"

	       // Normalize point into lattice space (0–1)
	       "vec3 local = clamp((inVec - minP) / (maxP - minP), 0.0, 1.0);\n"

	       // Scale to grid
	       "vec3 gridPos = local * vec3(xSize - 1, ySize - 1, zSize - 1);\n"

	       "ivec3 base = ivec3(int(floor(gridPos.x)),\n"
	       "int(floor(gridPos.y)),\n"
	       "int(floor(gridPos.z)));\n"
	       "vec3 frac = fract(gridPos);\n"

	       "vec3 result = vec3(0.0);\n"

	       // Trilinear interpolation
	       "for (int dz = 0; dz <= 1; dz++) {\n"
	       "for (int dy = 0; dy <= 1; dy++) {\n"
	       "for (int dx = 0; dx <= 1; dx++) {\n"

	       "int ix = clamp(base.x + dx, int(0), xSize - 1);\n"
	       "int iy = clamp(base.y + dy, int(0), ySize - 1);\n"
	       "int iz = clamp(base.z + dz, int(0), zSize - 1);\n"

	       "int idx = int(modifierIndex) + ((iz * ySize * xSize) + (iy * xSize) "
	       "+ ix) "
	       "* "
	       "3;\n "
	       "vec3 cp = vec3(\n"
	       "getDataFromVector(modifierData, idx),\n"
	       "getDataFromVector(modifierData, idx + 1),\n"
	       "getDataFromVector(modifierData, idx + 2)\n"
	       ");\n"

	       "float wx = dx == 0 ? (1.0 - frac.x) : frac.x;\n"
	       "float wy = dy == 0 ? (1.0 - frac.y) : frac.y;\n"
	       "float wz = dz == 0 ? (1.0 - frac.z) : frac.z;\n"

	       "float w = wx * wy * wz;\n"

	       "result += cp * w;\n"
	       "}\n"
	       "}\n"
	       "}\n"

	       "int pointCount = xSize * ySize * zSize;\n"
	       "modifierIndex += pointCount * 3;\n"

	       "return result;\n";
}

FFD::FFD(JaroViewer::ObjectManager* objectMan, size_t xSize, size_t ySize, size_t zSize)
  : mObjectMan(objectMan), mXSize(xSize), mYSize(ySize), mZSize(zSize) {
	mObjectMan->registerModel("ffdPoint", JaroViewer::cubeVertices, JaroViewer::PredefinedShader::WHITE, 0);
}

JaroViewer::ModifierParams FFD::getParams() const {
	assert(FFD::mRegistered && "Should be registered before use of params");

	const glm::vec3& minPoint = mInputData.minPoint;
	const glm::vec3& maxPoint = mInputData.maxPoint;
	JaroViewer::ModifierParams params{(float)FFD::mIdent, minPoint.x,
	                                  minPoint.y,         minPoint.z,
	                                  maxPoint.x,         maxPoint.y,
	                                  maxPoint.z,         (float)mXSize,
	                                  (float)mYSize,      (float)mZSize};
	params.reserve(10 + mPoints.size() * 3); // 10 = size of predefined params

	for (const auto& obj : mPoints) {
		const glm::vec3 pos = obj->getPosition();
		if (obj == mPoints.at(0)) std::cout << pos.x << std::endl;
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
		obj->setScale(0.03f);

		float x = i % mXSize;
		float y = (i / mXSize) % mYSize;
		float z = i / (mXSize * mYSize);

		obj->setTranslation(glm::vec3(
		  minP.x + (range.x) * (x / (float)(mXSize - 1)),
		  minP.y + (range.y) * (y / (float)(mYSize - 1)),
		  minP.z + (range.z) * (z / (float)(mZSize - 1))
		));

		mPoints.push_back(obj);

		obj->addListener([this](JaroViewer::RawObject*, JaroViewer::ObjectEvent event) {
			if (event != JaroViewer::ObjectEvent::TRANSFORM) return;
			glm::vec3 minPoint = glm::vec3(std::numeric_limits<float>().max());
			glm::vec3 maxPoint = glm::vec3(std::numeric_limits<float>().lowest());
			for (auto& obj : this->mPoints) {
				minPoint = glm::min(minPoint, obj->getPosition());
				maxPoint = glm::max(maxPoint, obj->getPosition());
			}

			bool changed = (minPoint != this->mOutputData.minPoint) ||
			  (maxPoint != this->mOutputData.maxPoint);
			this->mOutputData.minPoint = minPoint;
			this->mOutputData.maxPoint = maxPoint;
			if (changed) this->send(this, JaroViewer::ModifierEvent::OUTPUT_CHANGE);
			this->send(this, JaroViewer::ModifierEvent::UPDATE);
		});
	}
}

JaroViewer::Object FFD::getPoint(int x, int y, int z) {
	if (x >= mXSize || y >= mYSize || z >= mZSize) return nullptr;
	return mPoints.at(x + y * mXSize + z * mXSize * mYSize);
}
