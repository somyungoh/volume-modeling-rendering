#ifndef _SM_FIELD_OBJECT_H_
#define _SM_FIELD_OBJECT_H_
/*********************************************************************
*
*		shape.h
*
*		This class plays as an 'Obeject', which contains
*		ALL FIELDS one each. It will be used when building shapes
*
*********************************************************************/

#include "field.h"
#include "grid.h"
#include "transform.h"

class shape{

public:
	// constructors
	shape();
	shape(const color &baseColor);
	~shape();

	// getter, setters
	void setScalarField(fieldScalarPtr sf);
	///void setVectorField(fieldVectorPtr vf);
	///void setMatrixField(fieldMatrixPtr mf);
	fieldScalarPtr getScalarField() const;
	fieldVectorPtr getVectorField() const;
	fieldMatrixPtr getMatrixField() const;
	fieldScalarPtr  getScalarGrid()  const;

	color Color() const;

	// transforms
	void translate(const vec3 &dx);
	void scale(const vec3 &s);
	void rotate(const vec3 &axis, float angle);

private:
	// vectors of fields
	fieldScalarPtr scalarField;
	///fieldVectorPtr vectorField;
	///fieldMatrixPtr matrixField;
	color		   baseColor;
};

#endif // !_SM_FIELD_OBJECT_H_
