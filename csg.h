#ifndef _SM_CSG_H_
#define _SM_CSG_H_

/*********************************************************************
*
*		csg.h
*
*		Declaration of constructive solid geometry(CSG) operators:
*		Union, Intersection, Cutout
*
*		This is applied in the same way with the color field
*
*********************************************************************/

#include "field.h"


// ******	Scalar Field	****** //

// union operation
class scalarFieldUnion : public scalarField {

public:
	// constructors
	scalarFieldUnion();
	scalarFieldUnion(fieldScalarPtr field1, fieldScalarPtr field2);
	~scalarFieldUnion();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field1;
	const fieldScalarPtr field2;
};


// intersection operation
class scalarFieldIntersection : public scalarField {

public:
	// constructors
	scalarFieldIntersection();
	scalarFieldIntersection(fieldScalarPtr field1, fieldScalarPtr field2);
	~scalarFieldIntersection();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field1;
	const fieldScalarPtr field2;
};


// cutout operation
class scalarFieldCutout : public scalarField {

public:
	// constructors
	scalarFieldCutout();
	scalarFieldCutout(fieldScalarPtr field1, fieldScalarPtr field2);
	~scalarFieldCutout();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field1;
	const fieldScalarPtr field2;
};


// cutout shell
class scalarFieldShell : public scalarField {

public:
	// constructors
	scalarFieldShell();
	scalarFieldShell(fieldScalarPtr field1, float thickness);
	~scalarFieldShell();

	const fieldType eval(const vec3 &p) const;

private:
	const fieldScalarPtr field;
	const float h;
};


#endif // !_SM_CSG_H_
