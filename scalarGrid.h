#ifndef _SM_SCALARGRID_H_
#define _SM_SCALARGRID_H_

// ********************************* //
// *
// *	scalarGrid.h
// *
// *	collection of scalar grids
// *	- level set
// * 	- DSM
// * 	- wisp
// *
// ********************************* //

#include "grid.h"
#include "light.h"
#include "noise.h"
#include "perlinNoise.h"
#include <string>

// scalarGrid 
class scalarGridLevelSet : public grid<float> {
public:
	// inherit parent consturctors
	using grid<float>::grid;

	const gridType eval(const vec3 &p) const;
	void generate(fieldScalarPtr sdf, std::string fname);

private:
};


// scalarGrid 
class scalarGridDSM : public grid<float> {
public:
	// inherit parent consturctors
	using grid<float>::grid;

	const gridType eval(const vec3 &p) const;
	void generate(fieldScalarPtr sf, const std::vector<light*> &lights, float ds, std::string fname);

private:
};


// WISP
class scalarGridWISP : public grid<float> {
public:
	// inherit parent consturctors
	using grid<float>::grid;

	const gridType eval(const vec3 &p) const;
	void generate(const Noise_t &particle, const Noise_t &disNoise, int nWispDots, std::string fname);
	void clearMemory();

private:
	fractalSum<perlinNoiseGustavson> noise1;	// FSPN
	fractalSum<perlinNoiseGustavson> noise2;	// FSPN

	void stampWispDot(const vec3 &p, float density, const color &c);
};

#endif // !_SM_SCALARGRID_H_
