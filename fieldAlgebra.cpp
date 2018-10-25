#include "fieldAlgebra.h"
/*********************************************************************
*
*		fieldAlgebra.cpp
*
*		Implementation of field algebra.
*
*		Dev Note:
*		Vector Field Divide :: Might cause /0 error... at eval
*
*********************************************************************/


// ************************************ //
//  define field algebra classes  	//
// ************************************ //

// scalar add [f = f1 + f2]
scalarFieldAdd::scalarFieldAdd() : field1(NULL), field2(NULL) {};
scalarFieldAdd::scalarFieldAdd(fieldScalarPtr f1, fieldScalarPtr f2) : field1(f1), field2(f2) {};
scalarFieldAdd::~scalarFieldAdd() {};
const scalarFieldAdd::fieldType scalarFieldAdd::eval(const vec3 &p) const { return field1->eval(p) + field2->eval(p); };

// scalar subtract [f = f1 - f2]
scalarFieldSubtract::scalarFieldSubtract() : field1(NULL), field2(NULL) {};
scalarFieldSubtract::scalarFieldSubtract(fieldScalarPtr f1, fieldScalarPtr f2) : field1(f1), field2(f2) {};
scalarFieldSubtract::~scalarFieldSubtract() {};
const scalarFieldSubtract::fieldType scalarFieldSubtract::eval(const vec3 &p) const { return field1->eval(p) - field2->eval(p); };

// scalar divide [f = f1 / f2]
scalarFieldDivide::scalarFieldDivide() : field1(NULL), field2(NULL) {};
scalarFieldDivide::scalarFieldDivide(fieldScalarPtr f1, fieldScalarPtr f2) : field1(f1), field2(f2) {};
scalarFieldDivide::~scalarFieldDivide() {};
const scalarFieldDivide::fieldType scalarFieldDivide::eval(const vec3 &p) const { return std::isinf(field1->eval(p) / field2->eval(p)) ? 0 : field1->eval(p) / field2->eval(p); };

// scalar reciprocal [f = 1 / f1]
scalarFieldReciprocal::scalarFieldReciprocal() : field(NULL) {};
scalarFieldReciprocal::scalarFieldReciprocal(fieldScalarPtr f) : field(f) {};
scalarFieldReciprocal::~scalarFieldReciprocal() {};
const scalarFieldReciprocal::fieldType scalarFieldReciprocal::eval(const vec3 &p) const { return std::isinf(1 / field->eval(p)) ? 0 : field->eval(p); };

// scalar inverse [f = -f]
scalarFieldInverse::scalarFieldInverse() : field(NULL) {};
scalarFieldInverse::scalarFieldInverse(fieldScalarPtr f) : field(f) {};
scalarFieldInverse::~scalarFieldInverse() {};
const scalarFieldInverse::fieldType scalarFieldInverse::eval(const vec3 &p) const { return -1 * field->eval(p); };

// scalar clamp
scalarFieldClamp:: scalarFieldClamp() : field(NULL), min(0), max(1) {};
scalarFieldClamp:: scalarFieldClamp(fieldScalarPtr f, float min, float max) : field(f), min(min), max(max) {};
scalarFieldClamp::~ scalarFieldClamp() {};
//const  scalarFieldClamp::fieldType  scalarFieldClamp::eval(const vec3 &p) const { return (field->eval(p) < min ? min : field->eval(p)) > max ? max : field->eval(p); };
const  scalarFieldClamp::fieldType  scalarFieldClamp::eval(const vec3 &p) const { return field->eval(p) < min ? min : max; };

// scalar divide [f = f1 / f2]
scalarFieldVecDot::scalarFieldVecDot() : field1(NULL), field2(NULL) {};
scalarFieldVecDot::scalarFieldVecDot(fieldVectorPtr v1, fieldVectorPtr v2) : field1(v1), field2(v2) {};
scalarFieldVecDot::~scalarFieldVecDot() {};
const scalarFieldVecDot::fieldType scalarFieldVecDot::eval(const vec3 &p) const { return glm::dot(field1->eval(p), field2->eval(p)); };

// vector add [v = v1 + v2]
vectorFieldAdd::vectorFieldAdd() : field1(NULL), field2(NULL) {};
vectorFieldAdd::vectorFieldAdd(fieldVectorPtr v1, fieldVectorPtr v2) : field1(v1), field2(v2) {};
vectorFieldAdd::~vectorFieldAdd() {};
const vectorFieldAdd::fieldType vectorFieldAdd::eval(const vec3 &p) const { return field1->eval(p) + field2->eval(p); };

// vector subtract [v = v1 - v2]
vectorFieldSubtract::vectorFieldSubtract() : field1(NULL), field2(NULL) {};
vectorFieldSubtract::vectorFieldSubtract(fieldVectorPtr v1, fieldVectorPtr v2) : field1(v1), field2(v2) {};
vectorFieldSubtract::~vectorFieldSubtract() {};
const vectorFieldSubtract::fieldType vectorFieldSubtract::eval(const vec3 &p) const { return field1->eval(p) - field2->eval(p); };

// vector multiply [v = v * f]
vectorFieldMultiply::vectorFieldMultiply() : field1(NULL), field2(NULL) {};
vectorFieldMultiply::vectorFieldMultiply(fieldVectorPtr v, fieldScalarPtr f) : field1(v), field2(f) {};
vectorFieldMultiply::~vectorFieldMultiply() {};
const vectorFieldMultiply::fieldType vectorFieldMultiply::eval(const vec3 &p) const { return field1->eval(p) * field2->eval(p); };

// vector divide [v = v / f]
vectorFieldDivide::vectorFieldDivide() : field1(NULL), field2(NULL) {};
vectorFieldDivide::vectorFieldDivide(fieldVectorPtr v, fieldScalarPtr f) : field1(v), field2(f) {};
vectorFieldDivide::~vectorFieldDivide() {};
const vectorFieldDivide::fieldType vectorFieldDivide::eval(const vec3 &p) const { return field1->eval(p) / field2->eval(p); };

// vector cross product [v = v1 X v2]
vectorFieldCross::vectorFieldCross() : field1(NULL), field2(NULL) {};
vectorFieldCross::vectorFieldCross(fieldVectorPtr v1, fieldVectorPtr v2) : field1(v1), field2(v2) {};
vectorFieldCross::~vectorFieldCross() {};
const vectorFieldCross::fieldType vectorFieldCross::eval(const vec3 &p) const { return glm::cross(field1->eval(p), field2->eval(p)); };

// vector matrix multiply [v = v * m]
vectorFieldVecMatMult::vectorFieldVecMatMult() : field1(NULL), field2(NULL) {};
vectorFieldVecMatMult::vectorFieldVecMatMult(fieldVectorPtr v, fieldMatrixPtr m) : field1(v), field2(m) {};
vectorFieldVecMatMult::~vectorFieldVecMatMult() {};
const vectorFieldVecMatMult::fieldType vectorFieldVecMatMult::eval(const vec3 &p) const { return field1->eval(p) * glm::transpose(field2->eval(p)); };	// transpose matrix due to glm-matrix-column based representation.

// matrix - vector multiply [v = m * v]																													
vectorFieldMatVecMult::vectorFieldMatVecMult() : field1(NULL), field2(NULL) {};
vectorFieldMatVecMult::vectorFieldMatVecMult(fieldMatrixPtr m, fieldVectorPtr v) : field1(m), field2(v) {};
vectorFieldMatVecMult::~vectorFieldMatVecMult() {};
const vectorFieldMatVecMult::fieldType vectorFieldMatVecMult::eval(const vec3 &p) const { return glm::transpose(field1->eval(p)) * field2->eval(p); };	// transpose matrix due to glm-matrix-column based representation.

// vector outer product [m = v & v]	
matrixFieldOuter::matrixFieldOuter() : field1(NULL), field2(NULL) {};
matrixFieldOuter::matrixFieldOuter(fieldVectorPtr v1, fieldVectorPtr v2) : field1(v1), field2(v2) {};
matrixFieldOuter::~matrixFieldOuter() {};
const matrixFieldOuter::fieldType matrixFieldOuter::eval(const vec3 &p) const { return glm::outerProduct(field2 -> eval(p), field1-> eval(p)); };	// change vector order due to glm-matrix-column based representation.

// matrix addition [m = m1 + m2]																																		
matrixFieldAdd::matrixFieldAdd() : field1(NULL), field2(NULL) {};
matrixFieldAdd::matrixFieldAdd(fieldMatrixPtr m1, fieldMatrixPtr m2) : field1(m1), field2(m2) {};
matrixFieldAdd::~matrixFieldAdd() {};
const matrixFieldAdd::fieldType matrixFieldAdd::eval(const vec3 &p) const { return field1->eval(p) + field2->eval(p); };

// matrix subtraction [m = m1 - m2]	
matrixFieldSubtract::matrixFieldSubtract() : field1(NULL), field2(NULL) {};
matrixFieldSubtract::matrixFieldSubtract(fieldMatrixPtr m1, fieldMatrixPtr m2) : field1(m1), field2(m2) {};
matrixFieldSubtract::~matrixFieldSubtract() {};
const matrixFieldSubtract::fieldType matrixFieldSubtract::eval(const vec3 &p) const { return field1->eval(p) - field2->eval(p); };

// matrix multiplication [m = m1 * m2]	
matrixFieldMultiply::matrixFieldMultiply() : field1(NULL), field2(NULL) {};
matrixFieldMultiply::matrixFieldMultiply(fieldMatrixPtr m1, fieldMatrixPtr m2) : field1(m1), field2(m2) {};
matrixFieldMultiply::~matrixFieldMultiply() {};
const matrixFieldMultiply::fieldType matrixFieldMultiply::eval(const vec3 &p) const { return field2->eval(p) * field1->eval(p); };		// reverse matrix order due to glm-matrix-column based representation.



// *****************************//
//		operator overloading      //
// **************************** //

// scalar fields
const scalarFieldAdd			operator +(const field<float> &f1, const field<float> &f2) { return scalarFieldAdd((fieldScalarPtr)&f1, (fieldScalarPtr)&f2); };
inline const scalarFieldSubtract	operator -(const field<float> &f1, const field<float> &f2) { return scalarFieldSubtract((fieldScalarPtr)&f1, (fieldScalarPtr)&f2); };
inline const scalarFieldDivide		operator /(const field<float> &f1, const field<float> &f2) { return scalarFieldDivide((fieldScalarPtr)&f1, (fieldScalarPtr)&f2); };
inline const scalarFieldVecDot		operator ^(const field<vec3>  &v1, const field<vec3>  &v2) { return scalarFieldVecDot((fieldVectorPtr)&v1, (fieldVectorPtr)&v2); };

// vector fields
inline const vectorFieldAdd			operator +(const field<vec3> &v1, const field<vec3> &v2) { return vectorFieldAdd((fieldVectorPtr)&v1, (fieldVectorPtr)&v2); };
inline const vectorFieldSubtract	operator -(const field<vec3> &v1, const field<vec3> &v2) { return vectorFieldSubtract((fieldVectorPtr)&v1, (fieldVectorPtr)&v2); };
inline const vectorFieldMultiply	operator *(const field<vec3>  &v, const field<float> &f) { return vectorFieldMultiply((fieldVectorPtr)&v, (fieldScalarPtr)&f); };
inline const vectorFieldMultiply	operator *(const field<float> &f, const field<vec3>  &v) { return vectorFieldMultiply((fieldVectorPtr)&v, (fieldScalarPtr)&f); };
inline const vectorFieldDivide		operator /(const field<vec3>  &v, const field<float> &f) { return vectorFieldDivide((fieldVectorPtr)&v, (fieldScalarPtr)&f); };
inline const vectorFieldDivide		operator /(const field<float> &f, const field<vec3>  &v) { return vectorFieldDivide((fieldVectorPtr)&v, (fieldScalarPtr)&f); };
inline const vectorFieldCross		operator %(const field<vec3> &v1, const field<vec3> &v2) { return vectorFieldCross((fieldVectorPtr)&v1, (fieldVectorPtr)&v2); };
inline const vectorFieldVecMatMult	operator *(const field<vec3>  &v, const field<mat3>  &m) { return vectorFieldVecMatMult((fieldVectorPtr)&v, (fieldMatrixPtr)&m); };
inline const vectorFieldMatVecMult	operator *(const field<mat3>  &m, const field<vec3>  &v) { return vectorFieldMatVecMult((fieldMatrixPtr)&m, (fieldVectorPtr)&v); };

// matrix fields
inline const matrixFieldOuter		operator &(const field<vec3> &v1, const field<vec3> &v2) { return matrixFieldOuter((fieldVectorPtr)&v1, (fieldVectorPtr)&v2); };
inline const matrixFieldAdd			operator +(const field<mat3> &m1, const field<mat3> &m2) { return matrixFieldAdd((fieldMatrixPtr)&m1, (fieldMatrixPtr)&m2); };
inline const matrixFieldSubtract	operator -(const field<mat3> &m1, const field<mat3> &m2) { return matrixFieldSubtract((fieldMatrixPtr)&m1, (fieldMatrixPtr)&m2); };
inline const matrixFieldMultiply	operator *(const field<mat3> &m1, const field<mat3> &m2);

