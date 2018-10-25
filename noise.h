#ifndef _SM_NOISE_H_
#define _SM_NOISE_H_

// ******************************************************
// * 
// *	 noise.h
// *
// *	 A base code provided in the class
// *
// * 	 General purpose noise code
// * 	 Integrates multiple noise sources into a single framework
// * 
// *******************************************************


#include "gmath.h"
#include <vector>

struct Noise_t{

	Noise_t() :
		frequency(1),
		translate(vec3(0, 0, 0)),
		octaves(1.0),
		amplitude(1),
		exponent(1),
		offset(0),
		fjump(2),
		roughness(0.5),
		density(1.0),
		radius(1.0),
		pscale(1.0),
		Dscale(1.0),
		gamma(1.0),
		clump(1.0),
		time(0.0),
		fftLowCutoff(0.01),
		fftHighCutoff(1.0),
		fftPower(3.5),
		fftNbGridPoints(128),
		fftLength(10.0),
		lognormalmean(1.0),
		gaussianstandarddeviation(1.0),
		seed(12345),
		tangent(vec3(0, 0, 1)),
		normal(vec3(0, 1, 0)),
		binormal(vec3(1, 0, 0)),
		axis(vec3(0, 1, 0)),
		angle(0.0),
		P(vec3(0, 0, 0)),
		v(vec3(0, 0, 0)),
		A(vec3(0, 0, 0)),
		age(0.0),
		lifeTime(1.0),
		shutter(0.5),
		frameRate(1.0 / 24.0),
		falloff(1.0)

	{}

	float frequency;
	vec3  translate;
	float octaves;		// # of layers of smaller noises on top
	float amplitude;	// amplitude of the noise intensity
	float exponent;		// exponent term to frequencty - lets stay at 1
	float offset;
	float fjump;
	float roughness;
	float density;
	float radius;
	float pscale;		// particle size
	float Dscale;		// displacement scale to WISP dots
	float gamma;		// power of gamma, at the final step
	float clump;
	float time;
	float fftLowCutoff;
	float fftHighCutoff;
	float fftPower;
	int   fftNbGridPoints;
	float fftLength;
	float lognormalmean;
	float gaussianstandarddeviation;
	int   seed;
	vec3 tangent;
	vec3 normal;
	vec3 binormal;
	vec3 axis;
	float angle;
	vec3 P;				// position
	vec3 v;				// velocity
	vec3 A;				// acceleration
	float  age;
	float lifeTime;
	float shutter;
	float frameRate;
	float falloff;
};


class noise{
public:

	noise() {}
	virtual ~noise() {}

	virtual const float eval(const float x) const { return 0; }
	virtual const float eval(const vec3& x) const { return 0; }

	virtual void setParameters(const Noise_t& parameters) {}
	virtual void getParameters(Noise_t& parameters) const {}
};


template< typename BaseNoise>
class fractalSum : public noise{

public:
	fractalSum() :
		octaves(3.0),
		fjump(2.0),
		roughness(0.5),
		frequency(0.666666),
		translate(vec3(0, 0, 0)),
		offset(0.0),
		axis(vec3(0, 0, 1)),
		angle(0.0)
	{}

	~fractalSum() {}

	const float eval(const float x) const{

		float exp = exponent;
		float amp = 1;
		float accum = 0;
		int ioct = (int)octaves;
		for (int oc = 0; oc<ioct; oc++)
		{
			const float X = (x - translate[0]) * frequency * exp;
			accum += amp * _noise.eval(X);
			exp *= fjump;
			amp *= roughness;
		}
		const float X = (x - translate[0]) * frequency * exp;
		float val = amp * _noise.eval(X);
		accum += (octaves - (int)octaves) * val;
		
		float result = accum + offset;
		return result;
	}

	const float eval(const vec3& x) const{

		float exp = exponent;	// these are differ from variables in parameter object
		float amp = 1;
		float accum = 0;
		int ioct = (int)octaves;
		vec3 X = (x - translate);
		if (angle != 0.0)
		{
			float ca = cos(angle);
			float sa = sin(angle);
			X = X * ca + axis * glm::dot(axis, X) * (1.0f - ca) + glm::cross(axis, X) * sa;
		}
		X *= frequency*exp;
		for (int oc = 0; oc<ioct; oc++)
		{
			accum += amp * _noise.eval(X);
			X *= fjump;
			amp *= roughness;
		}
		float val = amp * _noise.eval(X);
		accum += (octaves - (int)octaves) * val;
		
		// manually added
		float result = accum + offset;
		return result;
	}


	void setParameters(const Noise_t& parameters){

		gamma		= parameters.gamma;
		amplitude	= parameters.amplitude;
		exponent	= parameters.exponent;
		octaves		= parameters.octaves;
		clump		= parameters.clump;
		fjump		= parameters.fjump;
		roughness	= parameters.roughness;
		falloff		= parameters.falloff;
		frequency	= parameters.frequency;
		translate	= parameters.translate;
		offset		= parameters.offset;
		axis		= parameters.axis;
		angle		= parameters.angle;
		_noise.setTime(parameters.time);
	}


	void getParameters(Noise_t& parameters) const{

		parameters.gamma		= gamma;
		parameters.amplitude	= amplitude;
		parameters.exponent		= exponent;
		parameters.octaves		= octaves;
		parameters.fjump		= fjump;
		parameters.falloff		= falloff;
		parameters.clump		= clump;
		parameters.roughness	= roughness;
		parameters.frequency	= frequency;
		parameters.translate	= translate;
		parameters.offset		= offset;
		parameters.axis			= axis;
		parameters.angle		= angle;
	}



private:

	BaseNoise _noise;

	float gamma;
	float amplitude;
	float exponent;
	float octaves;
	float fjump;
	float falloff;
	float clump;
	float roughness;
	float frequency;
	vec3 translate;
	float offset;
	vec3 axis;
	float angle;
};


#endif // !_SM_NOISE_H_
