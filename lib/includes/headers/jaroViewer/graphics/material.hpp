#pragma once

#include "jaroViewer/graphics/texture2D.hpp"
#include "jaroViewer/rendering/shader.hpp"

#include <string>

namespace JaroViewer {
	struct MaterialArgs {
		std::string diffusePath;
		std::string specularPath;
		float shininess;
	};
	struct ColorMaterialArgs {
		glm::vec4 diffuse;
		glm::vec4 specular;
		float shininess;
	};

	class Material {
	public:
		Material(const Texture2D& diffuse, const Texture2D& specular, float shininess);
		Material(const MaterialArgs& args);
		Material(const ColorMaterialArgs& args);

		void load(const Shader* shader, uint offset = 0) const;
		void loadIntoArray(const Shader* shader, int arrayIndex, uint offset = 0) const;

	private:
		std::string mVariableName;
		std::string mArrayName;

		Texture2D mDiffuse;
		Texture2D mSpecular;
		float mShininess;
	};
} // namespace JaroViewer
