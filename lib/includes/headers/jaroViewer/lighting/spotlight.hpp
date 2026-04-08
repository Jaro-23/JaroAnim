#pragma once

#include "jaroViewer/core/tools.hpp"
#include "jaroViewer/scene/object.hpp"

namespace JaroViewer {
	class Spotlight {
	public:
		struct SpotlightStruct {
			glm::vec3 position;
			float cutOff;
			glm::vec3 direction;
			float outerCutOff;
			glm::vec3 ambient;
			float constant;
			glm::vec3 diffuse;
			float linear;
			glm::vec3 specular;
			float quadratic;
			int enable;
			float pad0;
			float pad1;
			float pad2;
		};

		Spotlight(
		  Object obj,
		  glm::vec3 direction,
		  Tools::LightColor lightColor,
		  Tools::AttenuationParams params,
		  float innerAngle,
		  float outerAngle
		);

		void enable(bool enable);
		bool getState() const;
		SpotlightStruct getStruct() const;
		Object getObject();

		void setDirection(const glm::vec3& direction);
		glm::vec3 getDirection() const;

	private:
		Object mObject;
		Tools::LightColor mLightColor;
		bool mEnable;

		glm::vec3 mDirection;
		float mCutOff;
		float mOuterCutOff;

		float mConstant;
		float mLinear;
		float mQuadratic;
	};
} // namespace JaroViewer
