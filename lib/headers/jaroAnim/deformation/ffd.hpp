#pragma once

#include <jaroViewer/modifiers/autoModifier.hpp>

namespace JaroAnim {
	class FFD : public JaroViewer::AutoModifier<FFD> {
	public:
		static std::string getCode();
		JaroViewer::ModifierParams getParams() const override;
	};
} // namespace JaroAnim
