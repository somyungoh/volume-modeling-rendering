#ifndef _SM_RENDER_H_
#define _SM_RENDER_H_

/*********************************************************
*
*		render.h
*
*		A core class that handles overall framework
*		Precondition: target image size(imgX, imgY) 
*
*		Dev Note(9.16)
*		- Havent done anti-aliasing yet
*
*********************************************************/

#include "scalarField.h"
#include "fieldAlgebra.h"
#include "csg.h"
#include "transform.h"
#include "camera.h"
#include "scene.h"
#include "shape.h"

class render{

public:
	// constructors
	render();
	render(int imgX, int imgY);
	~render();

	// MAIN RUN RENDERING METHOD
	// precondition:  pixel map pointer that refers to image data
	// postcondition: passes back the pixel map with rendered image
	void run(float *(&pixmap));

	// view controllers
	void moveIn(float ds);
	void moveOut(float ds);
	void rotate(float da);

	// TEMPORARY METHODS TO CONTROL WITH UI
	void    getNoiseParameters(Noise_t& parameters) const;
	void    setNoiseParameters(const Noise_t& parameters);

private:
	// member variables
	int Nx, Ny;
	camera cam;		// main camera
	scene  scene;	// main scene

	// helper methods	//

	// postcondition: initializes core objects - scene, camera
	void init();

	void generateDSM();
	// computes the color of that ray in the space, solving Kajiya's Rendering Equation
	// precondition: a ray corresponding to the pixel, scale clipping values(sNear, sFar)
	//				 coefficient K for physical artifacts, derivative s(ds), offset control(t, 0< t <ds)
	// postconditon: Accumulates, returns the color along the ray
	color ray_march(const vec3 &ray, float sNear, float sFar, float ds, float dls, float K);

	// this method marches the ray towards the light
	color light_march(const vec3 &position, float ds);
};

#endif // !_SM_RENDER_H_
