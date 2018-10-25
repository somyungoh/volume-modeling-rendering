#include "light.h"

/*********************************************************
*
*		light.cpp
*
*		Implementation of a light class
*
**********************************************************/

light::light() {};
light::light(const vec3 &o, const color &c, float i) 
	: origin(o), lightColor(c), intensity(i) {};
light::~light() {};


// getters, setters
vec3  light::Origin()		const { return origin;     };
vec3  light::Normal()		const { return normal;	   };
color light::Color()		const { return lightColor; };
float light::Intensity()	const { return intensity;  };

fieldScalarPtr light::getDSM() { return dsm; };
void light::setDSM(fieldScalarPtr _dsm) { dsm = _dsm; };