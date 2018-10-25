#include "render.h"
#include <iostream>

/*********************************************************************
*
*		render.cpp
*
*		Main renderer class
*
*********************************************************************/

#define USE_LIGHTS
#define TEMP_SNEAR	4
#define TEMP_SFAR	7

// simple noise [30sec]
#define TEMP_DS		0.05
#define TEMP_DLS	0.05
#define TEMP_K		5		// ** This one is critical

// constructors
render::render() {};
render::render(int imgX, int imgY) : Nx(imgX), Ny(imgY) { init(); };
render::~render() {};

void render::moveIn(float ds)  { cam.moveIn(ds);  };
void render::moveOut(float ds) { cam.moveOut(ds); };
void render::rotate(float da)  { cam.rotate(da);  };

void render::init() {

	// initialize camera //

	vec3  cameraOrigin	= vec3(0, 0, -6);
	vec3  cameraView	= glm::normalize(vec3(0,0,0) - cameraOrigin);
	vec3  cameraUp		= vec3(0, 1, 0);
	float cameraFov		= 30.f;
	float cameraAspectR	= (float)Nx / Ny;
	
	// init. objects
	cam	= camera(cameraOrigin, cameraView, cameraUp, cameraFov, cameraAspectR);
	scene.init();

	// DSM Setting
	scene.useDSM(false);
};

// MAIN RUN RENDERING METHOD
void render::run(float *(&pixmap)) {
	
	for (int j = 0; j < Ny; j++) {
#pragma omp parallel for
		for (int i = 0; i < Nx; i++) {
			
			// compute colors
			vec3 ray = cam.getRay(i, j, Nx, Ny);		// this pixel's ray
			color c  = ray_march(ray, TEMP_SNEAR, TEMP_SFAR, TEMP_DS, TEMP_DLS, TEMP_K);			// this pixel's color (ray marching)

			// assign colors to pixel map
			pixmap[(j * Nx + i) * 4 + 0] = c.r;
			pixmap[(j * Nx + i) * 4 + 1] = c.g;
			pixmap[(j * Nx + i) * 4 + 2] = c.b;
			pixmap[(j * Nx + i) * 4 + 3] = c.a;
		}
	}
}

color render::ray_march(const vec3 &ray, float sNear, float sFar, float ds, float dls, float K) {

	// Kajuya's Rendering Equation:
	// [INTEGRAL](s) * K * Color(P) * Density(P) * Transmissity(P)

	// initialize base components to compute integral ds
	// number of steps(N) is decided by [ds]
	vec3  xp = cam.Origin() + ray * sNear;	// first position
	color L  = color(0, 0, 0, 1);			// color attenuated by length (init. black)
	float N  = (float)(sFar - sNear) / (ds);		// total sample N
	float T  = 1;							// total transmissity
	float dt = 0;							// dt

	// iteratively, running over the samples [0, 1 ... N]
	// solve the rendering equation
	for (int j = 0; j < N; j++) {
		
		// prepare variables
		float density;
		color cx;
		
		// perform eval()
		scene.eval(xp, density, cx);
		density = density < 0 ? 0 : density;	// masking

		xp += ray * ds;													// 1. compute X(p,s)
		dt  = exp(-1.f * K * ds * density);								// 2. Density(X)	*It is important try to stay exp(K), 0 < K < ds
		
#ifdef USE_LIGHTS
		if(density > 0)L  += light_march(xp, dls) * cx * (1 - dt) * T;	// 3. Color(X)
#else
		if (density > 0)L += cx * (1 - dt) * T;	// 3. Color(X)
#endif // USE_LIGHTS

		T *= dt;														// 4. Transmissity
	}
	L.a = (1 - T);

	return L;	// return final L (color)
};


// this method marches the ray towards the light
color render::light_march(const vec3 &xp, float dls) {
	
	color finalColor(0, 0, 0, 1);
	
	// march through all the lights
	for (int j = 0; j < scene.lightSize(); j++) {

		// *** initialize *** //
		float sl  = glm::length(scene.getLight(j)->Origin() - xp);		// distance between light - point
		vec3  nl  = glm::normalize(scene.getLight(j)->Origin() - xp);	// normal to light - point
		vec3  xls = xp + dls * nl;										// position by current ds
		float M	  = sl / dls;												// total number of steps
		float DSM = 0.0f;												// deep shadow map (DSM)

		// *** March *** //
		// if using DSM, get from dsm
		if (scene.isUsingDSM()) {
			DSM = scene.getLight(j)->getDSM()->eval(xp);
		}
		// if not, brute-force
		else {
			// march through the steps
			for (int i = 0; i < M; i++) {
				// check all objects
				float density;
				scene.eval(xls, density, color());

				density = density < 0 ? 0 : density;	// masking
				DSM		+= density * dls;				// update DSM
				xls		+= nl * dls;
			}
		}
		finalColor += scene.getLight(j)->Color() * scene.getLight(j)->Intensity() * exp(-(float)TEMP_K * DSM);
	}	// end of light marching
	return finalColor;
};

// ***** TEMPORARY METHODS ******** //
void  render::getNoiseParameters(Noise_t& parameters) const { scene.getNoiseParameters(parameters); };
void  render::setNoiseParameters(const Noise_t& parameters) { scene.setNoiseParameters(parameters); }
