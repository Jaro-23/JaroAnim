#pragma once

#include <array>
#include <glm/glm.hpp>
#include <memory>

#include "directionalLight.hpp"
#include "pointLight.hpp"
#include "spotlight.hpp"

namespace JaroViewer {
	class LightSet {
	public:
		static const unsigned int mMAXNUMDIRLIGHTS   = 2;
		static const unsigned int mMAXNUMPOINTLIGHTS = 20;
		static const unsigned int mMAXNUMSPOTLIGHTS  = 10;

		struct LightSetStruct {
			DirectionalLight::DirectionalLightStruct directionalLights[mMAXNUMDIRLIGHTS];
			PointLight::PointLightStruct pointLights[mMAXNUMPOINTLIGHTS];
			Spotlight::SpotlightStruct spotlights[mMAXNUMSPOTLIGHTS];
			int numDirLights;
			int numPointLights;
			int numSpotlights;
		};

		LightSet();
		void addDirLight(std::shared_ptr<DirectionalLight> dirLight);
		void addPointLight(std::shared_ptr<PointLight> pointLight);
		void addSpotlight(std::shared_ptr<Spotlight> spotlight);

		LightSetStruct getStruct() const;

	private:
		std::array<std::shared_ptr<DirectionalLight>, mMAXNUMDIRLIGHTS> mDirectionalLights;
		std::array<std::shared_ptr<PointLight>, mMAXNUMPOINTLIGHTS> mPointLights;
		std::array<std::shared_ptr<Spotlight>, mMAXNUMSPOTLIGHTS> mSpotlights;

		int mNumDirLights;
		int mNumPointLights;
		int mNumSpotlights;
	};
} // namespace JaroViewer
