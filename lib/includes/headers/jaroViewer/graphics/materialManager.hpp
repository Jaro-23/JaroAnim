#pragma once

#include "material.hpp"
#include "texture2D.hpp"

#include <map>
#include <memory>
#include <vector>

namespace JaroViewer {
	class MaterialManager {
	public:
		MaterialManager();

		uint createNew();
		void addMaterial(uint ident, const MaterialArgs& args);
		void addMaterial(uint ident, const ColorMaterialArgs& args);
		void resetLastShader() { mLastShader = nullptr; }

		void loadMaterial(Shader* shader, uint ident, uint offset = 0);

	private:
		std::vector<std::vector<Material>> mMaterials;
		std::map<std::string, std::shared_ptr<Texture2D>> mTextures;
		uint mLastMaterial;
		Shader* mLastShader; // Only used to compare in loading, not for use
	};
} // namespace JaroViewer
