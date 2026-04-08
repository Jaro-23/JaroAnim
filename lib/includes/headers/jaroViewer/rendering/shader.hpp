#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

namespace JaroViewer {
	struct ShaderCode {
		const std::string& vertexCode;
		const std::string& geometryCode;
		const std::string& fragmentCode;
	};

	struct ShaderPaths {
		std::vector<std::string>& vertexPaths;
		std::vector<std::string>& geometryPaths;
		std::vector<std::string>& fragmentPaths;
	};

	class Shader {
	public:
		Shader(const ShaderCode& code);
		Shader(const ShaderPaths& paths);

		void use() const;

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setUniformBuffer(const std::string& name, int position) const;

		void setFloat1(const std::string& name, float x) const;
		void setFloat2(const std::string& name, float x, float y) const;
		void setFloat3(const std::string& name, float x, float y, float z) const;
		void setFloat4(const std::string& name, float x, float y, float z, float w) const;

		void setVec3(const std::string& name, glm::vec3 vec) const;
		void setMat3(const std::string& name, glm::mat3 mat) const;
		void setMat4(const std::string& name, glm::mat4 mat) const;

	private:
		unsigned int
		  createShaderFromFile(uint shaderType, const std::vector<std::string>* sources, const std::string& errorName);
		unsigned int createShaderFromString(uint shaderType, const char* code, const std::string& errorName);
		void createProgram(unsigned int vertexID, unsigned int geometryID, unsigned int fragmentID);
		void checkCompilingError(unsigned int shaderID, const std::string& shaderName) const;
		void checkLinkingError(unsigned int programID) const;
		int getLocation(const std::string& name) const;

		unsigned int mProgramId;
	};
}; // namespace JaroViewer
