#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace JaroViewer {
	class Tools {
	public:
		template<typename T, typename Allocator>
		static unsigned int
		  generateBuffer(const std::vector<T, Allocator>& data, unsigned int bufferType, unsigned int usage);

		static glm::mat3 getNormalModelMatrix(const glm::mat4& model);
		static void readFile(const std::string& filePath, std::string* out);

		template<class... Ts>
		struct Overloaded : Ts... {
			using Ts::operator()...;
		};

		struct LightColor {
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
		};

		struct AttenuationParams {
			float constant;
			float linear;
			float quadratic;
		};
	};
} // namespace JaroViewer
