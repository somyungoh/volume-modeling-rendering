#ifndef _SM_FIELD_ALGEBRA_H_
#define _SM_FIELD_ALGEBRA_H_

/****************************************************************
*
*		fieldAlgebra.h
*
*		Declaration of field algebra.
*
*		[special vector operators]
*		v ^ v : dot product
*		v % v : cross product
*		v & v : outer product
*
****************************************************************/

#include "field.h"


// ************************************ //
//		define field algebra classes	//
// ************************************ //

// scalar add [f = f1 + f2]
class scalarFieldAdd : public field<float> {

public:
	// constructors
	scalarFieldAdd();
	scalarFieldAdd(fieldScalarPtr field1, fieldScalarPtr field2);
	~scalarFieldAdd();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field1;
	const fieldScalarPtr field2;
};


// scalar subtract [f = f1 - f2]
class scalarFieldSubtract : public field<float> {

public:
	// constructors
	scalarFieldSubtract();
	scalarFieldSubtract(fieldScalarPtr field1, fieldScalarPtr field2);
	~scalarFieldSubtract();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field1;
	const fieldScalarPtr field2;
};


// scalar divide [f = f1 / f2]
class scalarFieldDivide : public field<float> {

public:
	// constructors
	scalarFieldDivide();
	scalarFieldDivide(fieldScalarPtr field1, fieldScalarPtr field2);
	~scalarFieldDivide();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field1;
	const fieldScalarPtr field2;
};


// scalar reciprocal [f = 1 / f1]
class scalarFieldReciprocal : public field<float> {

public:
	// constructors
	scalarFieldReciprocal();
	scalarFieldReciprocal(fieldScalarPtr field);
	~scalarFieldReciprocal();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
};


// scalar inverse [f = -f]
class scalarFieldInverse : public field<float> {

public:
	// constructors
	scalarFieldInverse();
	scalarFieldInverse(fieldScalarPtr field);
	~scalarFieldInverse();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
};


// scalar clamp
class scalarFieldClamp : public field<float> {

public:
	// constructors
	scalarFieldClamp();
	scalarFieldClamp(fieldScalarPtr field, float min, float max);
	~scalarFieldClamp();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
	const float			 min, max;
};


// vector dot product [f = v1 / v2]
class scalarFieldVecDot : public field<float> {

public:
	// constructors
	scalarFieldVecDot();
	scalarFieldVecDot(fieldVectorPtr field1, fieldVectorPtr field2);
	~scalarFieldVecDot();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldVectorPtr field2;
};


// vector add [v = v1 + v2]
class vectorFieldAdd : public field<vec3> {

public:
	// constructors
	vectorFieldAdd();
	vectorFieldAdd(fieldVectorPtr field1, fieldVectorPtr field2);
	~vectorFieldAdd();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldVectorPtr field2;
};


// vector subtract [v = v1 - v2]
class vectorFieldSubtract : public field<vec3> {

public:
	// constructors
	vectorFieldSubtract();
	vectorFieldSubtract(fieldVectorPtr field1, fieldVectorPtr field2);
	~vectorFieldSubtract();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldVectorPtr field2;
};


// vector multiply [v = v * f]
class vectorFieldMultiply : public field<vec3> {

public:
	// constructors
	vectorFieldMultiply();
	vectorFieldMultiply(fieldVectorPtr field1, fieldScalarPtr field2);
	~vectorFieldMultiply();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldScalarPtr field2;
};


// vector divide [v = v / f]
class vectorFieldDivide : public field<vec3> {

public:
	// constructors
	vectorFieldDivide();
	vectorFieldDivide(fieldVectorPtr field1, fieldScalarPtr field2);
	~vectorFieldDivide();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldScalarPtr field2;
};


// vector cross product [v = v1 X v2]
class vectorFieldCross : public field<vec3> {

public:
	// constructors
	vectorFieldCross();
	vectorFieldCross(fieldVectorPtr field1, fieldVectorPtr field2);
	~vectorFieldCross();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldVectorPtr field2;
};


// vector - matrix multiply [v = v * m]
class vectorFieldVecMatMult : public field<vec3> {

public:
	// constructors
	vectorFieldVecMatMult();
	vectorFieldVecMatMult(fieldVectorPtr field1, fieldMatrixPtr field2);
	~vectorFieldVecMatMult();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldMatrixPtr field2;
};


// matrix - vector multiply [v = m * v]
class vectorFieldMatVecMult : public field<vec3> {

public:
	// constructors
	vectorFieldMatVecMult();
	vectorFieldMatVecMult(fieldMatrixPtr field1, fieldVectorPtr field2);
	~vectorFieldMatVecMult();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldMatrixPtr field1;
	const fieldVectorPtr field2;
};


// vector outer product [m = v & v]
class matrixFieldOuter : public field<mat3> {

public:
	// constructors
	matrixFieldOuter();
	matrixFieldOuter(fieldVectorPtr field1, fieldVectorPtr field2);
	~matrixFieldOuter();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldVectorPtr field1;
	const fieldVectorPtr field2;
};


// matrix addition [m = m1 + m2]
class matrixFieldAdd : public field<mat3> {

public:
	// constructors
	matrixFieldAdd();
	matrixFieldAdd(fieldMatrixPtr field1, fieldMatrixPtr field2);
	~matrixFieldAdd();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldMatrixPtr field1;
	const fieldMatrixPtr field2;
};


// matrix subtraction [m = m1 - m2]
class matrixFieldSubtract : public field<mat3> {

public:
	// constructors
	matrixFieldSubtract();
	matrixFieldSubtract(fieldMatrixPtr field1, fieldMatrixPtr field2);
	~matrixFieldSubtract();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldMatrixPtr field1;
	const fieldMatrixPtr field2;
};


// matrix multiplication [m = m1 * m2]
class matrixFieldMultiply : public field<mat3> {

public:
	// constructors
	matrixFieldMultiply();
	matrixFieldMultiply(fieldMatrixPtr field1, fieldMatrixPtr field2);
	~matrixFieldMultiply();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldMatrixPtr field1;
	const fieldMatrixPtr field2;
};



// *****************************//
//		operator overloading	//
// **************************** //

const scalarFieldAdd			operator +(const field<float> &f1, const field<float> &f2);
inline const scalarFieldSubtract	operator -(const field<float> &f1, const field<float> &f2);
inline const scalarFieldDivide		operator /(const field<float> &f1, const field<float> &f2);
inline const scalarFieldVecDot		operator ^(const field<vec3>  &v1, const field<vec3>  &v2);

inline const vectorFieldAdd			operator +(const field<vec3>  &v1, const field<vec3>  &v2);
inline const vectorFieldSubtract	operator -(const field<vec3>  &v1, const field<vec3>  &v2);
inline const vectorFieldMultiply	operator *(const field<vec3>  &v,  const field<float> &f);
inline const vectorFieldMultiply	operator *(const field<float> &f,  const field<vec3>  &v);
inline const vectorFieldDivide		operator /(const field<vec3>  &v,  const field<float> &f);
inline const vectorFieldDivide		operator /(const field<float> &f,  const field<vec3>  &v);
inline const vectorFieldCross		operator %(const field<vec3>  &v1, const field<vec3>  &v2);
inline const vectorFieldVecMatMult	operator *(const field<vec3>  &v,  const field<mat3>  &m);
inline const vectorFieldMatVecMult	operator *(const field<mat3>  &m, const field<vec3>   &v);

inline const matrixFieldOuter		operator &(const field<vec3>  &v1, const field<vec3>  &v2);
inline const matrixFieldAdd			operator +(const field<mat3>  &m1, const field<mat3>  &m2);
inline const matrixFieldSubtract	operator -(const field<mat3>  &m1, const field<mat3>  &m2);
inline const matrixFieldMultiply	operator *(const field<mat3>  &m1, const field<mat3>  &m2);


#endif // !_SM_FIELD_ALGEBRA_H_
