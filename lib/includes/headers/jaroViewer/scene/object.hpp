#pragma once

#include "glm/fwd.hpp"
#include "jaroViewer/modifiers/modifier.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <memory>
#include <sys/types.h>

namespace JaroViewer {
	struct ModifierStack {
		uint count;
		std::vector<float> params;
	};

	enum ObjectEvent { MODIFIER, DELETE, TRANSFORM, VISIBILITY };

	using Object    = std::shared_ptr<class RawObject>;
	using ObjectRef = std::weak_ptr<class RawObject>;
	class RawObject : public EventSender<RawObject, ObjectEvent> {
	public:
		RawObject(glm::vec3 minPoint, glm::vec3 maxPoint);
		RawObject(const RawObject&)            = delete;
		RawObject& operator=(const RawObject&) = delete;
		RawObject(RawObject&& other) noexcept;
		// RawObject& operator=(RawObject&& other) noexcept;
		~RawObject();

		void setVisibility(bool visibility);
		bool getVisibility() const;
		glm::mat4 getModelMatrix() const;
		glm::vec3 getPosition() const;

		glm::vec3 getEulerAngles() const;
		glm::quat getQuaternion() const;

		// Manage child objects
		void addChild(Object child);
		void removeChild(Object child);

		// Addition transform
		void addTranslation(const glm::vec3& translation);
		void addRotation(float angleX, float angleY, float angleZ);
		void addScale(const glm::vec3& scale);
		void addScale(float scale);

		// Set transform
		void setTranslation(const glm::vec3& translation);
		void setRotation(float angleX, float angleY, float angleZ);
		void setScale(const glm::vec3& scale);
		void setScale(float scale);

		// Modifiers
		void addModifier(std::shared_ptr<Modifier> modifier);
		ModifierStack getStack() const;

	protected:
		glm::mat4 getRotationMatrix(const glm::quat& q);
		void applyRotationRecursive(const glm::quat& delta, const glm::vec3& pivot);
		void applyScaleRecursive(const glm::vec3& scale, const glm::vec3& pivot);

		// Data
		std::vector<Object> mChildren;
		const glm::vec3 mMinPoint;
		const glm::vec3 mMaxPoint;

		glm::vec3 mTranslation;
		glm::quat mRotation;
		glm::vec3 mScale;
		bool mVisibility;

		// Modifiers
		std::vector<std::shared_ptr<Modifier>> mModifiers;
	};

} // namespace JaroViewer
