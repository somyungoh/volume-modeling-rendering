#ifndef _SM_FIELD_H_
#define _SM_FIELD_H_

/*********************************************************
*
*		field.h
*
*		Base class template of all fields
*
**********************************************************/

#include "gmath.h"
#include <algorithm>

// Setting up logic to be able to determine the data type of the gradient 
template <typename U>
struct gradType
{
	typedef int GType;
};

template<>
struct gradType<float>
{
	typedef vec3 GType;
};

template<>
struct gradType<vec3>
{
	typedef mat3 GType;
};

// template class for all the field classes
template<typename T>
class field{

public:
	field() {};
	virtual ~field() {};

	typedef T fieldType;
	typedef typename gradType<T>::GType gradType;

	virtual const fieldType eval(const vec3 &p) const { fieldType base{}; return base; };
	virtual const gradType  grad(const vec3 &p) const { gradType  base{}; return base; };
};

// define field pointer types
typedef field<float>  scalarField;
typedef field<vec3>   vectorField;
typedef field<color>  colorField;
typedef field<mat3>   matrixField;
typedef field<float>* fieldScalarPtr;
typedef field<vec3>*  fieldVectorPtr;
typedef field<color>* fieldColorPtr;
typedef field<mat3>*  fieldMatrixPtr;

#endif // !_SM_FIELD_H_
