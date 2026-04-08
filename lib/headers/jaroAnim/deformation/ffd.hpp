#pragma once

#include "jaroViewer/scene/object.hpp"
#include "jaroViewer/scene/objectManager.hpp"
#include <jaroViewer/modifiers/autoModifier.hpp>

namespace JaroAnim {
	class FFD : public JaroViewer::AutoModifier<FFD> {
	public:
		static std::string getCode();

		FFD(JaroViewer::ObjectManager* objectMan, size_t xSize, size_t ySize, size_t zSize);
		JaroViewer::ModifierParams getParams() const override;
		void updateData(JaroViewer::ObjectData inputData) override;
		JaroViewer::Object getPoint(int x, int y, int z);

	private:
		void resetPoints();
		void recomputeBounds();

		JaroViewer::ObjectManager* mObjectMan;
		size_t mXSize, mYSize, mZSize;
		std::vector<JaroViewer::Object> mPoints;
	};
} // namespace JaroAnim
