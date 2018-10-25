#ifndef  _SM_CAMERA_H_
#define  _SM_CAMERA_H_

/****************************************************
*
*		camera.h
*
*		A camera model for the scene
*
*****************************************************/

#include "gmath.h"

class camera{

public:
	// constructors
	camera();
	camera(const vec3 &origin, const vec3 &view, const vec3 &up, float fov, float aspectRatio);
	~camera();

	// getters
	vec3 Origin()  const;
	
	// camera controllers
	void moveIn (float ds);
	void moveOut(float ds);
	void rotate (float da);
	void moveTo(const vec3 &newOrigin);

	// methods
	vec3 getRay(int i, int j, int Nx, int Ny);

private:
	// member variables
	vec3  origin;			// camera positions
	vec3  view, up, right;	// camera coordinates
	float fov;				// field of view
	float aspectRatio;		// horizontal/vertical

};

#endif // ! _SM_CAMERA_H_
