#include "jaroAnim/interpolation/path.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>

using namespace JaroAnim;

Path Path::line(const glm::vec3& pointA, const glm::vec3& pointB) {
	return Path(
	  [pointA, pointB](double t) { return pointA.x + t * (pointB.x - pointA.x); },
	  [pointA, pointB](double t) { return pointA.y + t * (pointB.y - pointA.y); },
	  [pointA, pointB](double t) { return pointA.z + t * (pointB.z - pointA.z); }
	);
}

Path Path::circle(const glm::vec3& center, double radius) {
	return Path::spiral(center, radius, 0, 1);
}

Path Path::spiral(const glm::vec3& center, double radius, double height, double rotations) {
	return Path(
	  [center, radius, height, rotations](double t) {
		  return center.x + std::cos(2 * std::numbers::pi * t * rotations) * radius;
	  },
	  [center, radius, height, rotations](double t) {
		  return center.y + height * t;
	  },
	  [center, radius, height, rotations](double t) {
		  return center.z + std::sin(2 * std::numbers::pi * t * rotations) * radius;
	  }
	);
}

Path::Path(PathEval xEq, PathEval yEq, PathEval zEq)
  : mXEq(xEq), mYEq(yEq), mZEq(zEq) {
	loadPoints();
}

void Path::reverse() {
	mReverse = !mReverse;
	loadPoints();
}

glm::vec3 Path::rawInterpolate(double t) const {
	double clamped = std::clamp(t, 0.0, 1.0);
	if (mReverse) clamped = 1.0 - clamped;
	glm::vec3 pos = glm::vec3(mXEq(clamped), mYEq(clamped), mZEq(clamped));
	return pos;
}

glm::vec3 Path::distInterpolate(double t) const {
	double dist = mPoints.back().length * std::clamp(t, 0.0, 1.0);
	int index   = 0;
	while (index < mPoints.size() && mPoints.at(index).length <= dist) index++;

	if (index == 0) return rawInterpolate(0.0);
	if (index == mPoints.size()) return rawInterpolate(1.0);

	double interval = (dist - mPoints.at(index - 1).length) /
	  (mPoints.at(index).length - mPoints.at(index - 1).length);

	double tCalculated = mPoints.at(index - 1).t +
	  interval * (mPoints.at(index).t - mPoints.at(index - 1).t);
	return rawInterpolate(tCalculated);
}

void Path::loadPoints() {
	int count = (1.0 / mJump);
	mPoints   = std::vector<PathPoint>();
	mPoints.reserve(count);
	for (int i = 0; i <= count; ++i) {
		double t      = std::clamp(i * mJump, 0.0, 1.0);
		glm::vec3 pos = rawInterpolate(t);
		mPoints.push_back(
		  {t, pos,
		   (i == 0) ? 0.0 :
		              mPoints.at(i - 1).length + (mPoints.at(i - 1).position - pos).length()}
		);
	}
}
