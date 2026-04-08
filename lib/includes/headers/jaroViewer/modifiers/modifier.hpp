#pragma once

#include "jaroViewer/core/eventSender.hpp"

#include <glm/glm.hpp>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace JaroViewer {
	using ModifierParams = std::vector<float>;

	struct ObjectData {
		glm::vec3 minPoint;
		glm::vec3 maxPoint;
	};

	enum ModifierEvent { UPDATE, OUTPUT_CHANGE };

	class Modifier : public EventSender<Modifier, ModifierEvent> {
	public:
		static std::string getVertexLibrary();
		static std::optional<uint> registerModifier(const std::string& name, const std::string& funcCode);

		virtual ModifierParams getParams() const = 0;
		virtual void updateData(ObjectData inputData);
		ObjectData getOutputData() const;

	protected:
		ObjectData mInputData  = {glm::vec3(0.0f), glm::vec3(0.0f)};
		ObjectData mOutputData = {glm::vec3(0.0f), glm::vec3(0.0f)};

	private:
		struct RegisterEntry {
			uint ident;
			std::string code;
		};

		static std::map<std::string, RegisterEntry>& getModifiers();
		static uint& getNextIdent();

		static std::map<std::string, RegisterEntry> mModifiers;
		static uint mNextIdent;
	};
} // namespace JaroViewer
