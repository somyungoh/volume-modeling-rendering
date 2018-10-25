#ifndef _SM_GMATH_H_
#define _SM_GMATH_H_

/****************************************************************
*
*		gmath.h
*
*		Stores all mathatical needs for the project
*		- load glm
*
****************************************************************/

#include "glm\glm.hpp"
#include <random>
#include <functional>
#include <chrono>

#define PI 3.14159265359
#define EPSILON 0.000001

typedef glm::vec2	vec2;
typedef glm::vec3	vec3;
typedef glm::vec4	color;
typedef glm::mat3x3 	mat3;

// pauliMatrix for rotation matrix
const static mat3 pauliMatrix[3] = {
	mat3(
		0,0,0,
		0,0,1,
		0,-1,0),
	mat3(
		0,0,-1,
		0,0,0,
		1,0,0),
	mat3(
		0,1,0,
		-1,0,0,
		0,0,0)
};

// mersenne random twister integer
inline const int randomInt() {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> dis(0.0, generator.max());

	return dis(generator);
}

// mersenne random twister double
inline const double randomReal() {

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	float real_rand = dis(generator);

	return real_rand;
}

// rotation matrix
inline const mat3 rotationMatrix(const vec3 &axis, const double angle) {

	const float cosa = cos(angle);
	const float sina = sin(angle);
	vec3 ax = axis / sqrt(axis*axis);
	mat3 op = glm::outerProduct(ax, ax);
	mat3 result = mat3(1) * cosa
		+ op * (1.0f - cosa)
		+ pauliMatrix[0] * axis[0] * sina
		+ pauliMatrix[1] * axis[1] * sina
		+ pauliMatrix[2] * axis[2] * sina;
	return result;
};

// rodriques rotation formula
inline vec3 rodriguesRotation(const vec3 &v, const vec3 &axis, float angle) {
	
	const vec3 rv = v * (float)cos(angle * PI / 180.f) 
		+ glm::cross(axis, v)*(float)sin(angle * PI / 180.f)
		+ axis * glm::dot(axis, v) * (1 - (float)cos(angle * PI / 180.f));

	return rv;
}


#endif // !_SM_GMATH_H_
