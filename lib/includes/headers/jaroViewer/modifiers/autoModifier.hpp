#pragma once

#include "jaroViewer/modifiers/modifier.hpp"

namespace JaroViewer {
	template<typename T>
	class AutoModifier : public Modifier {
	protected:
		static uint mIdent;
		static bool mRegistered;
	};

	template<typename T>
	uint AutoModifier<T>::mIdent = 0;

	template<typename T>
	bool AutoModifier<T>::mRegistered = [] {
		if (AutoModifier<T>::mRegistered) return true;
		std::optional<uint> ident =
		  Modifier::registerModifier(typeid(T).name(), T::getCode());
		if (!ident.has_value()) {
			AutoModifier<T>::mIdent = 0;
			return false;
		}
		AutoModifier<T>::mIdent = ident.value();
		return true;
	}();
} // namespace JaroViewer
