#ifndef _SM_LIGHT_H_
#define _SM_LIGHT_H_

/****************************************************************
*
*		light.h
*
*		A light class.
*		Currently implemented following a point light model.
*
*		This class contains its own DSM.
*		It is initialized in construction step (default: 10^3)
*
****************************************************************/

#include "gmath.h"
#include "grid.h"
#include <string>

class light{

public:
	// constructors
	light();
	light(const vec3 &origin, const color &color, float intensity);
	~light();

	// getters, setters
	vec3  Origin()		const;
	vec3  Normal()		const;
	color Color()		const;
	float Intensity()	const;

	// DSM
	fieldScalarPtr getDSM();
	void setDSM(fieldScalarPtr dsm);

	//color InterpolatedColor(float t) const;	// t [0,1]
	//color setColor2(const color &c)	const;
	
private:
	vec3	origin;
	vec3	normal;
	color	lightColor;
	color	lightColor2;	// secret color2
	float	intensity;
	fieldScalarPtr dsm;
};

#endif // !_SM_LIGHT_H_
