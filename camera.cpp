#include "camera.h"
#include <iostream>

/*********************************************************
*
*		camera.cpp
*
*		Implementation of a camera model for the scene
*
**********************************************************/

// constructors
camera::camera() {};
camera::camera(const vec3 &o, const vec3 &v, const vec3 &up, float fov, float aRatio) 
	: origin(o), view(v), up(up), right(glm::cross(v, up)), fov(fov), aspectRatio(aRatio) {};
camera::~camera() {};

// getters
vec3 camera::Origin() const		{ return origin; };
void camera::moveIn(float ds)   	{ origin = origin + normalize(vec3(0, 0, 0) - origin)*ds; };
void camera::moveOut(float ds)		{ origin = origin - normalize(vec3(0, 0, 0) - origin)*ds; };
void camera::rotate(float da)		{ vec3 a(0, 1, 0); origin = rodriguesRotation(origin, a, da); right = rodriguesRotation(right, a, da); view = rodriguesRotation(view, a, da); };
void camera::moveTo(const vec3 &newO)	{ origin = newO; };

// methods

// precondition: pixel index(i, j), image size(Nx, Ny)
// returns ray vector proportion to the input
vec3 camera::getRay(int i, int j, int Nx, int Ny) {

	// compute pixel position in camera coordinates
	const float ui  = (-1 + 2 * ((float)i / (Nx - 1))) * tan((fov / 2) * (PI / 180.f));
	const float vj  = (-1 + 2 * ((float)j / (Ny - 1))) * tan((fov / 2) * (PI / 180.f)) / (aspectRatio);
	const vec3	puv = up * vj + right * ui;
	
	// compute final ray
	const vec3 nij = glm::normalize(puv + view);		// it is an normalized ray
	
	return nij;
}
