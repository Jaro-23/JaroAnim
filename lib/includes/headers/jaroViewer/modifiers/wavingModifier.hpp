#pragma once

#include "autoModifier.hpp"

namespace JaroViewer {
	class WavingModifier : public AutoModifier<WavingModifier> {
	public:
		static std::string getCode();
		ModifierParams getParams() const override;
		void setData(glm::vec3&, glm::vec3&) {}
	};
} // namespace JaroViewer
