#ifndef _SM_SCALARFIELD_H_
#define _SM_SCALARFIELD_H_

/****************************************************************
*
*		scalarField.h
*
*		Collection of scalar field class
*
****************************************************************/

#include "field.h"
#include "noise.h"
#include "perlinNoise.h"

// 1.sphere
class scalarFieldSphere : public field<float> {

public:
	scalarFieldSphere();
	scalarFieldSphere(const vec3 &center, float radius);
	~scalarFieldSphere();

	// member function
	const fieldType eval(const vec3 &p) const;	// float
	const gradType  grad(const vec3 &p) const;	// vector

	// getter,setter
	vec3  Center() const;
	float Radius() const;
	void  setCenter(const vec3 &center);
	void  setRadius(float radius);

private:
	vec3  center;
	float radius;
 };


// 2.ellipse
class scalarFieldEllipse : public field<float> {

public:

	scalarFieldEllipse();
	scalarFieldEllipse(const vec3 &center, const vec3 &stretch, float rMaj, float r2Min);
	~scalarFieldEllipse();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()  const;
	vec3  Stretch() const;
	float Radius1() const;
	float Radius2() const;
	void  setCenter (const vec3 &center);
	void  setStretch (const vec3 &normal);
	void  setRadiusMj(float radius1);
	void  setRadiusMn(float radius2);

private:
	vec3  center, stretch;
	float radiusMj, radiusMn;
};


// 3.torus
class scalarFieldTorus : public field<float> {

public:
	scalarFieldTorus();
	scalarFieldTorus(const vec3 &center, const vec3 &normal, float r1, float r2);
	~scalarFieldTorus();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()  const;
	vec3  Normal()  const;
	float Radius1() const;
	float Radius2() const;
	void  setCenter(const vec3 &center);
	void  setNormal(const vec3 &normal);
	void  setRadius1(float radius1);
	void  setRadius2(float radius2);

private:
	vec3  center, normal;
	float radius1, radius2;		// r1: outer r2: inner
};


// 4.box
class scalarFieldBox : public field<float> {

public:
	scalarFieldBox();
	scalarFieldBox(const vec3 &center, float radius, float exponent);
	~scalarFieldBox();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()  const;
	float Radius()  const;
	float Exp()		const;
	void  setCenter (const vec3 &center);
	void  setRadius (float radius);
	void  setExp	(float exp);

private:
	vec3  center;
	float radius, exp;		// exp: exponent (determines the edge curvature)
};


// 5.plane
class scalarFieldPlane : public field<float> {

public:
	scalarFieldPlane();
	scalarFieldPlane(const vec3 &center, const vec3 &normal);
	~scalarFieldPlane();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()  const;
	vec3  Normal()  const;
	void  setCenter(const vec3 &center);
	void  setNormal(const vec3 &normal);

private:
	vec3  center, normal;
};


// 6.cone
class scalarFieldCone : public field<float> {

public:
	scalarFieldCone ();
	scalarFieldCone (const vec3 &center, const vec3 &normal, float height, float angle);
	~scalarFieldCone();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()  const;
	vec3  Normal()  const;
	float Height()	const;
	float Angle()	const;
	void  setCenter(const vec3 &center);
	void  setNormal(const vec3 &normal);
	void  setHeight(float height);
	void  setAngle (float angle);

private:
	vec3  center, normal;
	float height, angle;
};


// 7.cylinder
class scalarFieldCylinder : public field<float> {

public:
	scalarFieldCylinder();
	scalarFieldCylinder(const vec3 &center, const vec3 &normal, float radius, float height);
	~scalarFieldCylinder();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()  const;
	vec3  Normal()  const;
	float Radius() const;
	void  setCenter(const vec3 &center);
	void  setNormal(const vec3 &normal);
	void  setRadius(float radius);

private:
	vec3  center, normal;
	float radius, height;
};

// 8.icosahedron
class scalarFieldIcosahedron : public field<float> {

public:
	scalarFieldIcosahedron();
	scalarFieldIcosahedron(const vec3 &center);
	~scalarFieldIcosahedron();

	// member funtions
	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;

	// getter,setter
	vec3  Center()		const;
	float Thickness()	const;
	void  setCenter(const vec3 &center);

private:
	vec3  center;
	float T;		// wire thickness
};

// 9.stenier patch
class scalarFieldStenier : public field<float> {

public:
	scalarFieldStenier();
	scalarFieldStenier(const vec3 &center);
	~scalarFieldStenier();

	// member funtions
	const fieldType eval(const vec3 &p) const;

	// getter,setter
	vec3  Center()	const;
	void  setCenter(const vec3 &center);

private:
	vec3  center;
};

// 10.pyroclasticSphere
class scalarFieldPyroclasticSphere : public field<float> {

public:
	scalarFieldPyroclasticSphere();
	scalarFieldPyroclasticSphere(const vec3 &center, float radius);
	~scalarFieldPyroclasticSphere();

	// member function
	const fieldType eval(const vec3 &p) const;	// float
	const gradType  grad(const vec3 &p) const;	// vector

	// getter,setter
	vec3  Center() const;
	float Radius() const;
	void  setCenter(const vec3 &center);
	void  setRadius(float radius);
	void  getNoiseParameters(Noise_t& parameters) const;
	void  setNoiseParameters(const Noise_t& parameters);
	
private:
	vec3  center;
	float radius;
	fractalSum<perlinNoiseGustavson> noise;
};

// 11.noise
class scalarFieldNoise : public field<float> {

public:
	scalarFieldNoise();
	scalarFieldNoise(const vec3 &center);
	~scalarFieldNoise();

	// member function
	const fieldType eval(const vec3 &p) const;	// float
	const gradType  grad(const vec3 &p) const;	// vector

	// getter,setter
	vec3  Center() const;
	void  setCenter(const vec3 &center);
	void  getNoiseParameters(Noise_t& parameters) const;
	void  setNoiseParameters(const Noise_t& parameters);

private:
	vec3  center;
	fractalSum<perlinNoiseGustavson> noise;
};


#endif // !_SM_SCALAFIELD_H_