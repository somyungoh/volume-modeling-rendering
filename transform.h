#ifndef _SM_TRANSFORM_H_
#define _SM_TRANSFORM_H_

/****************************************************************
*
*		transform.h
*
*		declaration of transform functions
*		[Translate, Scale, Rotation]
*
****************************************************************/

#include "field.h"

// scalar translate
class scalarFieldTranslate : public field<float> {

public:
	// constructors
	scalarFieldTranslate();
	scalarFieldTranslate(fieldScalarPtr field, const vec3 &dx);
	~scalarFieldTranslate();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
	const vec3			 dx;
};


// vector translate
class vectorFieldTranslate : public field<vec3> {

public:
	// constructors
	vectorFieldTranslate();
	vectorFieldTranslate(fieldVectorPtr field, const vec3 &dx);
	~vectorFieldTranslate();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field;
	const vec3			 dx;
};


// matrix translate
class matrixFieldTranslate : public field<mat3> {

public:
	// constructors
	matrixFieldTranslate();
	matrixFieldTranslate(fieldMatrixPtr field, const vec3 &dx);
	~matrixFieldTranslate();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldMatrixPtr field;
	const vec3			 dx;
};


// scalar scale
class scalarFieldScale : public field<float> {

public:
	// constructors
	scalarFieldScale();
	scalarFieldScale(fieldScalarPtr field, const vec3 &s);
	~scalarFieldScale();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
	const vec3			 s;
};


// vector Scale
class vectorFieldScale : public field<vec3> {

public:
	// constructors
	//vectorFieldScale();
	//vectorFieldScale(fieldVectorPtr field, const vec3 &s);
	//~vectorFieldScale();
	//
	//const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field;
	const vec3			 s;
};


// matrix Scale
class matrixFieldScale : public field<mat3> {

public:
	// constructors
	//matrixFieldScale();
	//matrixFieldScale(fieldMatrixPtr field, const vec3 &s);
	//~matrixFieldScale();
	//
	//const fieldType eval(const vec3 &p) const;

private:
	const fieldMatrixPtr field;
	const vec3			 s;
};


// scalar rotate
class scalarFieldRotate : public field<float> {

public:
	// constructors
	scalarFieldRotate();
	scalarFieldRotate(fieldScalarPtr field, const vec3 &axis, float angle);
	~scalarFieldRotate();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
	const vec3			 axis;
	const float			 angle;

	const vec3 rotate(const vec3 &p, float angle) const;
};


// vector Rotate
class vectorFieldRotate : public field<vec3> {

public:
	// constructors
	vectorFieldRotate();
	vectorFieldRotate(fieldVectorPtr field, const vec3 &axis, float angle);
	~vectorFieldRotate();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field;
	const vec3			 axis;
	const float			 angle;

	const vec3 rotate(const vec3 &p, float angle) const;
};


// matrix Rotate
class matrixFieldRotate : public field<mat3> {

public:
	// constructors
	matrixFieldRotate();
	matrixFieldRotate(fieldMatrixPtr field, const vec3 &axis, float angle);
	~matrixFieldRotate();

	const fieldType eval(const vec3 &p) const;
private:
	const fieldMatrixPtr field;
	const vec3			 axis;
	const float			 angle;

	const vec3 rotate(const vec3 &p, float angle) const;
};

#endif // !_SM_TRANSFORM_H_
