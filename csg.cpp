/*********************************************************************
*
*		csg.h
*
*		Implementation of constructive solid geometry(CSG) operators:
*
*********************************************************************/

#include "csg.h"

scalarFieldUnion::scalarFieldUnion() : field1(NULL), field2(NULL) {};
scalarFieldUnion::scalarFieldUnion(fieldScalarPtr f1, fieldScalarPtr f2) : field1(f1), field2(f2) {};
scalarFieldUnion::~scalarFieldUnion() {};
const scalarFieldUnion::fieldType scalarFieldUnion::eval(const vec3 &p) const { return std::max(field1->eval(p), field2->eval(p)); }

scalarFieldIntersection::scalarFieldIntersection() : field1(NULL), field2(NULL) {};
scalarFieldIntersection::scalarFieldIntersection(fieldScalarPtr f1, fieldScalarPtr f2) : field1(f1), field2(f2) {};
scalarFieldIntersection::~scalarFieldIntersection() {};
const scalarFieldIntersection::fieldType scalarFieldIntersection::eval(const vec3 &p) const { return std::min(field1->eval(p), field2->eval(p)); }

scalarFieldCutout::scalarFieldCutout() : field1(NULL), field2(NULL) {};
scalarFieldCutout::scalarFieldCutout(fieldScalarPtr f1, fieldScalarPtr f2) : field1(f1), field2(f2) {};
scalarFieldCutout::~scalarFieldCutout() {};
const scalarFieldCutout::fieldType scalarFieldCutout::eval(const vec3 &p) const { return std::min(field1->eval(p), -1.f * field2->eval(p)); }

scalarFieldShell::scalarFieldShell() : field(NULL), h(0) {};
scalarFieldShell::scalarFieldShell(fieldScalarPtr f, float thickness) : field(f), h(thickness) {};
scalarFieldShell::~scalarFieldShell() {};
const scalarFieldShell::fieldType scalarFieldShell::eval(const vec3 &p) const { return std::min((field->eval(p) + h / 2.f), -1.f * (field->eval(p) - h / 2.f)); }
