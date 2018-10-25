
/****************************************************************
*
*		transform.cpp
*
*		Implementation of transform functions
*		[Translate, Scale, Rotation]
*
****************************************************************/

#include "transform.h"

// scalar translate
scalarFieldTranslate::scalarFieldTranslate() : field(NULL), dx(0) {};
scalarFieldTranslate::scalarFieldTranslate(fieldScalarPtr f, const vec3 &dx) : field(f), dx(dx) {};
scalarFieldTranslate::~scalarFieldTranslate() {};
const scalarFieldTranslate::fieldType scalarFieldTranslate::eval(const vec3 &p) const { return field->eval(p - dx); };

// vector translate
vectorFieldTranslate::vectorFieldTranslate() : field(NULL), dx(0) {};
vectorFieldTranslate::vectorFieldTranslate(fieldVectorPtr v, const vec3 &dx) : field(v), dx(dx) {};
vectorFieldTranslate::~vectorFieldTranslate() {};
const vectorFieldTranslate::fieldType vectorFieldTranslate::eval(const vec3 &p) const { return field->eval(p - dx); };

// matrix translate
matrixFieldTranslate::matrixFieldTranslate() : field(NULL), dx(0) {};
matrixFieldTranslate::matrixFieldTranslate(fieldMatrixPtr m, const vec3 &dx) : field(m), dx(dx) {};
matrixFieldTranslate::~matrixFieldTranslate() {};
const matrixFieldTranslate::fieldType matrixFieldTranslate::eval(const vec3 &p) const { return field->eval(p - dx); };

// scalar scale
scalarFieldScale::scalarFieldScale() : field(NULL), s(0) {};
scalarFieldScale::scalarFieldScale(fieldScalarPtr f, const vec3 &s) : field(f), s(s) {};
scalarFieldScale::~scalarFieldScale() {};
const scalarFieldScale::fieldType scalarFieldScale::eval(const vec3 &p) const { return field->eval(p / s); };

// vector scale
//vectorFieldScale::vectorFieldScale() : field(NULL), s(0) {};
//vectorFieldScale::vectorFieldScale(fieldVectorPtr f, const vec3 &s) : field(f), s(s) {};
//vectorFieldScale::~vectorFieldScale() {};
//const vectorFieldScale::fieldType vectorFieldScale::eval(const vec3 &p) const { return field->eval(p / s) * s; };

// matrix scale
//matrixFieldScale::matrixFieldScale() : field(NULL), s(0) {};
//matrixFieldScale::matrixFieldScale(fieldMatrixPtr f, const vec3 &s) : field(f), s(s) {};
//matrixFieldScale::~matrixFieldScale() {};
//const matrixFieldScale::fieldType matrixFieldScale::eval(const vec3 &p) const { return field->eval(p / s) * s*s; };

// scalar rotate
scalarFieldRotate::scalarFieldRotate() : field(NULL), axis(vec3()), angle(0) {};
scalarFieldRotate::scalarFieldRotate(fieldScalarPtr f, const vec3 &axis, float angle) : field(f), axis(glm::normalize(axis)), angle(angle) {};
scalarFieldRotate::~scalarFieldRotate() {};
const scalarFieldRotate::fieldType scalarFieldRotate::eval(const vec3 &p) const { return field->eval(rotate(p, -angle)); };
const vec3 scalarFieldRotate::rotate(const vec3 &p, float a) const { return p * (float)cos(a * PI / 180.f) + axis * glm::dot(axis, p) * (float)(1 - cos(a * PI / 180.f)) + glm::cross(axis, p) * (float)sin(a * PI / 180.f); };

// vector rotate
vectorFieldRotate::vectorFieldRotate() : field(NULL), axis(vec3()), angle(0) {};
vectorFieldRotate::vectorFieldRotate(fieldVectorPtr v, const vec3 &axis, float angle) : field(v), axis(glm::normalize(axis)), angle(angle) {};
vectorFieldRotate::~vectorFieldRotate() {};
const vectorFieldRotate::fieldType vectorFieldRotate::eval(const vec3 &p) const { vec3 v_ = field->eval(rotate(p, -angle)); return glm::transpose(rotationMatrix(axis, angle)) * v_; };		// transpose matrix due to glm spec.
const vec3 vectorFieldRotate::rotate(const vec3 &p, float a) const { return p * (float)cos(a * PI / 180.f) + axis * glm::dot(axis, p) * (float)(1 - cos(a * PI / 180.f)) + glm::cross(axis, p) * (float)sin(a * PI / 180.f); };

// matrix rotate
matrixFieldRotate::matrixFieldRotate() : field(NULL), axis(vec3()), angle(0) {};
matrixFieldRotate::matrixFieldRotate(fieldMatrixPtr m, const vec3 &axis, float angle) : field(m), axis(glm::normalize(axis)), angle(angle) {};
matrixFieldRotate::~matrixFieldRotate() {};
const matrixFieldRotate::fieldType matrixFieldRotate::eval(const vec3 &p) const { mat3 m_ = field->eval(rotate(p, -angle)); return glm::transpose(rotationMatrix(axis, angle)) * m_ * rotationMatrix(axis, angle); };		// transpose matrix due to glm spec.
const vec3 matrixFieldRotate::rotate(const vec3 &p, float a) const { return p * (float)cos(a * PI / 180.f) + axis * glm::dot(axis, p) * (float)(1 - cos(a * PI / 180.f)) + glm::cross(axis, p) * (float)sin(a * PI / 180.f); };
