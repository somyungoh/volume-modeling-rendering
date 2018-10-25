#include "scalarField.h"

/*********************************************************
*
*		scalarField.cpp
*
*		Implementation of all the scalarField class
*		field<float>
*
**********************************************************/

// 1.sphere
scalarFieldSphere::scalarFieldSphere()  {};
scalarFieldSphere::scalarFieldSphere(const vec3 &c, float r) : center(c), radius(r) {};
scalarFieldSphere::~scalarFieldSphere() {};
vec3  scalarFieldSphere::Center() const			{ return center; };
float scalarFieldSphere::Radius() const			{ return radius; };
void  scalarFieldSphere::setCenter(const vec3 &c)	{ center = c; };
void  scalarFieldSphere::setRadius(float r)		{ radius = r; };
const scalarFieldSphere::fieldType scalarFieldSphere::eval(const vec3 &p) const { return (radius - glm::length(p - center)); };				// float
const scalarFieldSphere::gradType  scalarFieldSphere::grad(const vec3 &p) const { return -1.f * (p - center) / glm::length(p - center); };	// vector

// 2.ellipse
// NOTE: magnitude of the stretch is the amount of strength
scalarFieldEllipse::scalarFieldEllipse()  {};
scalarFieldEllipse::scalarFieldEllipse(const vec3 &c, const vec3 &s, float rMj, float rMn) : center(c), stretch(s), radiusMj(rMj), radiusMn(rMn) { };
scalarFieldEllipse::~scalarFieldEllipse() {};
vec3  scalarFieldEllipse::Center()  const		{ return center; };
vec3  scalarFieldEllipse::Stretch()  const		{ return stretch; };
float scalarFieldEllipse::Radius1() const		{ return radiusMj; };
float scalarFieldEllipse::Radius2() const		{ return radiusMn; };
void  scalarFieldEllipse::setCenter (const vec3 &c) 	{ center = c; };
void  scalarFieldEllipse::setStretch(const vec3 &n) 	{ stretch = n; };
void  scalarFieldEllipse::setRadiusMj(float r1)		{ radiusMj = r1; };
void  scalarFieldEllipse::setRadiusMn(float r2)		{ radiusMn = r2; };
const scalarFieldEllipse::fieldType scalarFieldEllipse::eval(const vec3 &p) const {
	
	vec3  x  = p - center;
	float Z  = glm::dot(x, stretch);
	vec3  xp = x - Z * stretch;

	return (1 - Z*Z/radiusMj*radiusMj - dot(xp,xp)/radiusMn*radiusMn); 
};				

// 3.torus
scalarFieldTorus::scalarFieldTorus() {};
scalarFieldTorus::scalarFieldTorus(const vec3 &c, const vec3 &n, float r1, float r2) : center(c), normal(n), radius1(r1), radius2(r2) {};
scalarFieldTorus::~scalarFieldTorus() {};
vec3  scalarFieldTorus::Center()  const			{ return center; };
vec3  scalarFieldTorus::Normal()  const			{ return normal; };
float scalarFieldTorus::Radius1() const			{ return radius1; };
float scalarFieldTorus::Radius2() const			{ return radius2; };
void  scalarFieldTorus::setCenter(const vec3 &c)	{ center = c; };
void  scalarFieldTorus::setNormal(const vec3 &n)	{ normal = n; };
void  scalarFieldTorus::setRadius1(float r1)		{ radius1 = r1; };
void  scalarFieldTorus::setRadius2(float r2)		{ radius2 = r2; };
const scalarFieldTorus::fieldType scalarFieldTorus::eval(const vec3 &p) const {
	
	vec3 x  = p - center;
	vec3 xp = x - glm::dot(x, normal) * normal;

	return (4.f * radius1*radius1 * dot(xp,xp)) - pow(dot(x,x) * radius1*radius1 - radius2*radius2, 2);
};

// 4.box
scalarFieldBox::scalarFieldBox()  {};
scalarFieldBox::scalarFieldBox(const vec3 &c, float r, float e) : center(c), radius(r), exp(e) {};
scalarFieldBox::~scalarFieldBox() {};
vec3  scalarFieldBox::Center()  const		{ return center; };
float scalarFieldBox::Radius()  const		{ return radius; };
float scalarFieldBox::Exp()		const	{ return exp;    };
void  scalarFieldBox::setCenter(const vec3 &c)	{ center = c; };
void  scalarFieldBox::setRadius(float r)	{ radius = r; };
void  scalarFieldBox::setExp(float e)		{ exp	 = e; };
const scalarFieldBox::fieldType scalarFieldBox::eval(const vec3 &p) const {

	vec3 x = p - center;

	return pow(radius, exp) - pow(x.x, exp) - pow(x.y, exp) - pow(x.z, exp);
};

// 5.plane
scalarFieldPlane::scalarFieldPlane() {};
scalarFieldPlane::scalarFieldPlane(const vec3 &c, const vec3 &n) : center(c), normal(n) {};
scalarFieldPlane::~scalarFieldPlane() {};
vec3  scalarFieldPlane::Center()  const		 { return center; };
vec3  scalarFieldPlane::Normal()  const		 { return normal; };
void  scalarFieldPlane::setCenter(const vec3 &c) { center = c; };
void  scalarFieldPlane::setNormal(const vec3 &n) { normal = n; };
const scalarFieldPlane::fieldType scalarFieldPlane::eval(const vec3 &p) const {
	
	vec3 x = p - center;

	return - glm::dot(x, normal);
};

// 6.cone
// NOTE: h-height, angle-spreadness
scalarFieldCone::scalarFieldCone() {};
scalarFieldCone::scalarFieldCone(const vec3 &c, const vec3 &n, float h, float a) : center(c), normal(n), height(h), angle(a) {};
scalarFieldCone::~scalarFieldCone() {};
vec3  scalarFieldCone::Center()  const		{ return center; };
vec3  scalarFieldCone::Normal()  const		{ return normal; };
float scalarFieldCone::Height()  const		{ return height; };
float scalarFieldCone::Angle()   const		{ return angle;  };
void  scalarFieldCone::setCenter(const vec3 &c) { center = c; };
void  scalarFieldCone::setNormal(const vec3 &n) { normal = n; };
void  scalarFieldCone::setHeight(float h)	{ height = h; };
void  scalarFieldCone::setAngle (float a)	{ angle  = a; };
const scalarFieldCone::fieldType scalarFieldCone::eval(const vec3 &p) const {

	vec3  x   = p - center;
	float xn  = glm::dot(x, normal);
	float det = xn - glm::length(x) * cos(angle * PI /180.f);

	if		(p == center)	return 0;
	else if	(xn < 0)		return xn;
	else if (xn > height)	return height - xn;
	//else					return xn - glm::length(x) * cos(angle * PI/180.f);
	else					return (angle * PI / 180.f) - std::acos(xn / glm::length(x));
};

// 7.cylinder
scalarFieldCylinder::scalarFieldCylinder() {};
scalarFieldCylinder::scalarFieldCylinder(const vec3 &c, const vec3 &n, float r, float h) : center(c), normal(n), radius(r), height(h) {};
scalarFieldCylinder::~scalarFieldCylinder() {};
vec3  scalarFieldCylinder::Center()  const		{ return center; };
vec3  scalarFieldCylinder::Normal()  const		{ return normal; };
float scalarFieldCylinder::Radius()  const		{ return radius; };
void  scalarFieldCylinder::setCenter(const vec3 &c)	{ center = c; };
void  scalarFieldCylinder::setNormal(const vec3 &n) 	{ normal = n; };
void  scalarFieldCylinder::setRadius(float r)		{ radius = r; };
const scalarFieldCylinder::fieldType scalarFieldCylinder::eval(const vec3 &p) const {

	vec3 x  = p - center;
	vec3 xpt = p - center + normal * height/ 2.f;
	vec3 xpb = p - center - normal * height / 2.f;
	float infCylinder = radius - glm::length(x - dot(x, normal) * normal);

	return std::min(std::min(infCylinder, glm::dot(xpt, normal)), glm::dot(xpb, -normal));
};

// 8.icosahedron
scalarFieldIcosahedron::scalarFieldIcosahedron() {};
scalarFieldIcosahedron::scalarFieldIcosahedron(const vec3 &c) : center(c), T(2.6180339f) {};
scalarFieldIcosahedron::~scalarFieldIcosahedron() {};
vec3  scalarFieldIcosahedron::Center()		const	{ return center; };
float scalarFieldIcosahedron::Thickness()	const	{ return T;	 };
void  scalarFieldIcosahedron::setCenter(const vec3 &c)	{ center = c;	 };
const scalarFieldIcosahedron::fieldType scalarFieldIcosahedron::eval(const vec3 &p) const {

	vec3  x  = p - center;
	float lx = glm::length(x);
	
	if (lx <= 1.8 * PI) return cos(x.x + T * x.y) + cos(x.x - T * x.y) + cos(x.y + T * x.z) + cos(x.y - T * x.z) + cos(x.z + T * x.x) + cos(x.z - T * x.x) - 2;
	else				return -1.8 * PI;
};

// 9.stenier patch
scalarFieldStenier::scalarFieldStenier() {};
scalarFieldStenier::scalarFieldStenier(const vec3 &c) : center(c) {};
scalarFieldStenier::~scalarFieldStenier() {};
vec3  scalarFieldStenier::Center()		const 	{ return center; };
void  scalarFieldStenier::setCenter(const vec3 &c) 	{ center = c; };
const scalarFieldStenier::fieldType scalarFieldStenier::eval(const vec3 &p) const {

	vec3  x = p - center;
	float X = x.x;
	float Y = x.y;
	float Z = x.z;

	return -(X*X*Y*Y + X*X*Z*Z + Y*Y*Z*Z - X*Y*Z);
};

// 10.pyroclastic sphere
scalarFieldPyroclasticSphere::scalarFieldPyroclasticSphere() {};
scalarFieldPyroclasticSphere::scalarFieldPyroclasticSphere(const vec3 &c, float r) : center(c), radius(r) {};
scalarFieldPyroclasticSphere::~scalarFieldPyroclasticSphere() {};
vec3  scalarFieldPyroclasticSphere::Center() 		const 	{ return center; };
float scalarFieldPyroclasticSphere::Radius() 		const 	{ return radius; };
void  scalarFieldPyroclasticSphere::setCenter(const vec3 &c) 	{ center = c; };
void  scalarFieldPyroclasticSphere::setRadius(float r) 		{ radius = r; };
const scalarFieldPyroclasticSphere::fieldType scalarFieldPyroclasticSphere::eval(const vec3 &p) const { 

	// Get parameters
	Noise_t param;
	noise.getParameters(param);

	// compute density
	float len = glm::length(p - center);
	float nv = noise.eval(glm::normalize(p) * radius);
	nv = param.amplitude * pow(std::abs(nv), param.gamma);
	
	if (len > radius + nv)	return 0;	// outside the sphere
	else					return 1;	
};
const scalarFieldPyroclasticSphere::gradType  scalarFieldPyroclasticSphere::grad(const vec3 &p) const { return -1.f * (p - center) / glm::length(p - center); };	// vector
void  scalarFieldPyroclasticSphere::getNoiseParameters(Noise_t& parameters) const { noise.getParameters(parameters); };
void  scalarFieldPyroclasticSphere::setNoiseParameters(const Noise_t& parameters) { noise.setParameters(parameters); };

// 11.noise
scalarFieldNoise::scalarFieldNoise() {};
scalarFieldNoise::scalarFieldNoise(const vec3 &c) : center(c) {};
scalarFieldNoise::~scalarFieldNoise() {};
vec3  scalarFieldNoise::Center() 		const 	{ return center; };
void  scalarFieldNoise::setCenter(const vec3 &c) 	{ center = c; };
const scalarFieldNoise::fieldType scalarFieldNoise::eval(const vec3 &p) const {

	// Get parameters
	Noise_t param;
	noise.getParameters(param);
	
	// compute noise
	float nv  = std::abs(noise.eval(p));	// noise value
	float len = glm::length(p - center);
	if (len > param.pscale)					// outside the sphere 
		return 0;
	else
		return nv * pow((1 - len / (float)param.pscale), param.falloff);
};
const scalarFieldNoise::gradType  scalarFieldNoise::grad(const vec3 &p) const { return -1.f * (p - center) / glm::length(p - center); };	// vector
void  scalarFieldNoise::getNoiseParameters(Noise_t& parameters) const { noise.getParameters(parameters); };
void  scalarFieldNoise::setNoiseParameters(const Noise_t& parameters) { noise.setParameters(parameters); };
