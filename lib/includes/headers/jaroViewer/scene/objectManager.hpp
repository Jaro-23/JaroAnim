#pragma once

#include "jaroViewer/graphics/materialManager.hpp"
#include "jaroViewer/rendering/gpuVector.hpp"
#include "jaroViewer/rendering/shader.hpp"
#include "jaroViewer/rendering/shaderManager.hpp"
#include "jaroViewer/scene/object.hpp"

#include <map>
#include <memory>
#include <string>
#include <sys/types.h>
#include <variant>
#include <vector>

namespace Assimp {
	class Importer;
}
struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace JaroViewer {
	enum class TextureType { DIFFUSE, SPECULAR, NORMAL, HEIGHT };

	struct Instance {
		ObjectRef object;
		glm::mat4 model;
		uint modifierStart;
		uint modifierCount;
	};

	struct InstanceData {
		glm::mat4 model;
		glm::mat3 normalModel;
		uint modifierStart;
		uint modifierCount;
	};

	struct Mesh {
		uint vao;
		uint instanceVBO;
		uint count;
		uint material;
		glm::vec3 minPoint;
		glm::vec3 maxPoint;
	};

	struct ModelState {
		std::vector<Mesh> meshes;
		bool useIndices;
		uint shader;
		GpuVector modifierData;
		std::vector<Instance> instances;
	};

	using ShaderParams =
	  std::variant<std::reference_wrapper<const ShaderCode>, std::reference_wrapper<const ShaderPaths>, uint>;

	class ObjectManager {
	public:
		ObjectManager();

		MaterialManager* getMaterialManager();

		void registerModel(const std::string& ident, const std::vector<float>& vertices, ShaderParams shaderParams, uint material);
		void registerModel(const std::string& ident, const std::string& modelPath, ShaderParams shaderParams);
		Object createObject(const std::string& model);

		void renderObjects(bool usingPostProcessor, const glm::vec3& viewPos);
		void renderRegions(const glm::vec3& viewPos);

		Object getFromObjectId(uint id) const;

	private:
		void updateModifierTex(const ModifierStack& stack, const std::string& model, uint instanceIdent);

		Mesh registerVerticesModel(const std::vector<float>& vertices, uint material);
		Mesh registerIndicesModel(const std::vector<float>& vertices, const std::vector<uint>& indices, uint material);
		uint handleBuffers();

		void registerFileModel(const std::string& ident, const std::string& modelPath, uint shader);
		void processNode(aiNode* node, const std::string& ident, const std::string& directory, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const std::string& directory, const aiScene* scene);
		std::vector<std::string> loadMaterials(aiMaterial* mat, TextureType type);

		size_t getNextFreeSlot(const std::string& model) const;

		std::map<std::string, ModelState> mModels;
		ShaderManager mShaderManager;
		MaterialManager mMaterialManager;
		std::shared_ptr<Assimp::Importer> mImporter;
	};
} // namespace JaroViewer
