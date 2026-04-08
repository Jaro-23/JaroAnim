#pragma once

#include "shader.hpp"
#include <map>

namespace JaroViewer {
	enum PredefinedShader { WHITE = 0, REGION = 1, BASIC = 2 };

	class ShaderManager {
	public:
		ShaderManager();

		uint loadShader(const ShaderCode& codes);
		uint loadShader(const ShaderPaths& paths);

		Shader* getShader(uint ident);
		bool activateShader(uint ident);

	private:
		std::string pathsToKey(const ShaderPaths& paths) const;

		std::map<std::string, uint> mPathToIdent;
		std::vector<Shader> mShaders;
		uint mActiveShader;
	};
} // namespace JaroViewer
