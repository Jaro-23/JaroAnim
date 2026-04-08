#include "jaroAnim/deformation/ffd.hpp"
#include <cassert>

using namespace JaroAnim;

std::string FFD::getCode() {
	return "vec3 outVec = inVec;\n outVec.y += "
	       "sin(inVec.x * 100.0) * 0.2;\n return outVec;\n";
}

JaroViewer::ModifierParams FFD::getParams() const {
	assert(FFD::mRegistered);
	return {(float)FFD::mIdent};
}
