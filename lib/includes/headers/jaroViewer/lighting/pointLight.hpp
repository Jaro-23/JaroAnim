#pragma once

#include "jaroViewer/core/tools.hpp"
#include "jaroViewer/scene/object.hpp"

#include <glm/glm.hpp>

namespace JaroViewer {
	class PointLight {
	public:
		struct PointLightStruct {
			glm::vec3 position;
			int enable;
			glm::vec3 ambient;
			float constant;
			glm::vec3 diffuse;
			float linear;
			glm::vec3 specular;
			float quadratic;
		};

		PointLight(Object obj, Tools::LightColor lightColor, Tools::AttenuationParams params);

		void enable(bool enable);
		PointLightStruct getStruct() const;
		Object getObject();

	private:
		Object mObject;
		Tools::LightColor mLightColor;
		bool mEnable;

		float mConstant;
		float mLinear;
		float mQuadratic;
	};
} // namespace JaroViewer
