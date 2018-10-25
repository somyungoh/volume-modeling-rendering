#include "scalarGrid.h"

/*********************************************************
*
*		scalarGrid.cpp
*
*		Implementation of scalar grids
*
**********************************************************/

// ******	Level Set	******* //

// returns density at point p
const scalarGridLevelSet::gridType scalarGridLevelSet::eval(const vec3 &p) const {

	// get grid value
	return trilinearInterpolate(p);
};

// generate and initialize grid data
// precondition: mesh object (.obj)
void scalarGridLevelSet::generate(fieldScalarPtr sdf, std::string fname) {

	initGrid();

	printf("levelSet::Start Generating Level Set...\n");
#pragma omp parallel for
	for (int k = 0; k < subdivZ; k++) {
		for (int j = 0; j < subdivY; j++) {
			for (int i = 0; i < subdivX; i++) {

				const vec3  xp = getWorldPositionAt(i, j, k);	// world position of g(i,j,k)
				const float sd = sdf->eval(xp);					// signed distance
				set(i, j, k, sd);
			}
		}
//		printf("levelSet::Generate %.2f percent done.\n", ((float)k / subdivZ) * 100);
	}
	write("Grid/LevelSet/lset_" + fname + std::string(".txt"));
	printf("levelSet::File Saved - %s\n", fname);
	printf("levelSet::Finished Generating Level Set.\n");
}


// ******	Deep Shadow Map(DSM)	******* //
// returns density at point p
const scalarGridDSM::gridType scalarGridDSM::eval(const vec3 &p) const {

	// get grid value
	return trilinearInterpolate(p);
};

// perform light march
void scalarGridDSM::generate(fieldScalarPtr sf, const std::vector<light*> &lights, float ds, std::string fname) {
	
	printf("DSM::Start Generating DSM...\n");

	for (int l = 0; l < lights.size(); l++) {
//#pragma omp parallel for
		for (int k = 0; k < subdivX; k++) {
			for (int j = 0; j <subdivY; j++) {
				for (int i = 0; i < subdivZ; i++) {
					// get grid point
					vec3 gridP = getWorldPositionAt(i, j, k);

					// run marching
					// initialize
					float sl = glm::length(lights.at(l)->Origin() - gridP);	// distance between light - point
					vec3  nl = glm::normalize(lights.at(l)->Origin() - gridP);	// normal to light - point
					vec3  xls = gridP + ds * nl;						// position by current ds
					float M = sl / ds;									// total number of steps
					float DSM = 0.0f;									// deep shadow map (DSM)
																		// march through the steps
					for (int i = 0; i < M; i++) {
						// check all objects
						float density = sf->eval(xls);
						density = density < 0 ? 0 : density;	// masking
						DSM += density * ds;					// update DSM
						xls += nl * ds;
						
					}
					// set value
					set(i, j, k, DSM);
				}
			}
//			printf("DSM::Generate %.2f percent done.\n", ((float)k / subdivZ) * 100);
		}
		write("Grids/DSM/dsm_" + fname + std::to_string(l) + std::string(".txt"));
		printf("DSM::File Saved - %s\n", fname);
	}
	printf("DSM::Finished Generating DSM.\n");
};




// ******	WISP	******* //


// returns density at point p
const scalarGridWISP::gridType scalarGridWISP::eval(const vec3 &p) const {
	
	// get grid value
	return trilinearInterpolate(p);
};

// generate wisp
// precondition: number of particles, wisp dots
void scalarGridWISP::generate(const Noise_t &particle, const Noise_t &disNoise, int nWispDots, std::string fname) {

	printf("WISP::Start generating...\n", fname);

	// init
	initGrid();
	std::mt19937 generator(time(0));
	std::uniform_real_distribution<float> dis(-1.f, 1.f);
	
	vec3 r0, r1, r2;
	vec3 p2, p3;
	vec3 D, O;

	// put different seeds
	noise1.setParameters(particle);
	noise2.setParameters(disNoise);

	// loop over dots
//#pragma omp parallel for
	for (int i = 0; i < nWispDots; i++) {
			
		// init dot position
		r0 = vec3(dis(generator), dis(generator), dis(generator));
	
		// move to unit sphere
		r1 = glm::normalize(r0);
			
		// displace radically
		float disp	= pow(std::fabs(noise1.eval(r0)),particle.clump);
		r2	= r1 * disp;

		// map to guide particle
		p2 = particle.P + r2 * particle.pscale;
			
		// another displacement
		O = vec3(0.1, 0.1, 0.1);	// offset
		D = vec3(noise2.eval(r2), noise2.eval(r2 + O), noise2.eval(r2 - O));			// displacement
		p3 = p2 + particle.Dscale * D;

		// ** STAMP To Grid **//
		stampWispDot(p3, particle.density, color(1, 1, 1, 1));
	}
	// save to file
	//write("Grids/WISP/wisp" + fname + std::string(".txt"));

	printf("WISP::File Saved - %s\n", fname);
	printf("WISP::Finished Generating WISP.\n");
};

void scalarGridWISP::clearMemory() { delete[] data; }

void scalarGridWISP::stampWispDot(const vec3 &p, float density, const color &c) {
	
	// trilinear interpolation

	float i = (p.x - LLC.x) / dx;
	float j = (p.y - LLC.y) / dy;
	float k = (p.z - LLC.z) / dz;
	
	float wi = i - std::floorf(i);	// weights
	float wj = j - std::floorf(j);
	float wk = k - std::floorf(k);

	i = std::floorf(i);
	j = std::floorf(j);
	k = std::floorf(k);
	
	// ignore outer bounds
	if (i < 0 || i + 1 > subdivX - 1
		|| j < 0 || j + 1 > subdivY - 1
		|| k < 0 || k + 1 > subdivZ - 1)
		return;

	// set to grid;
	add(i, j, k, density * (1 - wi) * (1 - wj) * (1 - wk));
	add(i + 1, j, k, density * (wi)	* (1 - wj) * (1 - wk));
	add(i, j + 1, k, density * (1 - wi) * (wj) * (1 - wk));
	add(i, j, k + 1, density * (1 - wi) * (1 - wj) * (wk));
	add(i + 1, j + 1, k, density * (wi) * (wj) * (1 - wk));
	add(i + 1, j, k + 1, density * (wi) * (1 - wj) * (wk));
	add(i, j + 1, k + 1, density * (1 - wi) * (wj) * (wk));
	add(i + 1, j + 1, k + 1, density * (wi) * (wj) * (wk));
}