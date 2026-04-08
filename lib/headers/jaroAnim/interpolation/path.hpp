#pragma once

#include <functional>
#include <glm/glm.hpp>

namespace JaroAnim {
	using PathEval = std::function<double(double)>;

	typedef struct {
		double t;
		glm::vec3 position;
		double length;
	} PathPoint;

	class Path {
	public:
		static Path line(const glm::vec3& pointA, const glm::vec3& pointB);
		static Path circle(const glm::vec3& center, double radius);
		static Path spiral(const glm::vec3& center, double radius, double height, double rotations);

		Path(PathEval xEq, PathEval yEq, PathEval zEq);
		void reverse();
		glm::vec3 rawInterpolate(double t) const;
		glm::vec3 distInterpolate(double t) const;

	private:
		void loadPoints();

		const double mJump = 0.005;
		bool mReverse      = false;
		PathEval mXEq, mYEq, mZEq;
		std::vector<PathPoint> mPoints;
	};
} // namespace JaroAnim
