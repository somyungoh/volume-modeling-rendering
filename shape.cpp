#include "shape.h"

/*********************************************************
*
*		fieldObject.cpp
*
*		Implementation of field object class
*
**********************************************************/

shape::shape() {}
shape::shape(const color &c) : baseColor(c) {}
shape::~shape() {}

void shape::setScalarField(fieldScalarPtr sf) { scalarField = sf; };
///void shape::setVectorField(fieldVectorPtr vf) { vectorField = vf; };
///void shape::setMatrixField(fieldMatrixPtr mf) { matrixField = mf; };
fieldScalarPtr shape::getScalarField() const  { return scalarField; };
///fieldVectorPtr shape::getVectorField() const  { return vectorField; };
///fieldMatrixPtr shape::getMatrixField() const  { return matrixField; };
color shape::Color() const { return baseColor; };


// transforms
// updates all the set 
void shape::translate(const vec3 &dx) {
	
	fieldScalarPtr sf = new scalarFieldTranslate(scalarField, dx);
	///fieldVectorPtr vf = new vectorFieldTranslate(vectorField, dx);
	///fieldMatrixPtr mf = new matrixFieldTranslate(matrixField, dx);
	setScalarField(sf);
	///setVectorField(vf);
	///setMatrixField(mf);
};
void shape::scale(const vec3 &s) {

	fieldScalarPtr sf = new scalarFieldScale(scalarField, s);
	//fieldVectorPtr vf = new vectorFieldScale(vectorField, s);
	//fieldMatrixPtr mf = new matrixFieldScale(matrixField, s);
	setScalarField(sf);
	//setVectorField(vf);
	//setMatrixField(mf);
};
void shape::rotate(const vec3 &axis, float angle) {

	fieldScalarPtr sf = new scalarFieldRotate(scalarField, axis, angle);
	///fieldVectorPtr vf = new vectorFieldRotate(vectorField, axis, angle);
	///fieldMatrixPtr mf = new matrixFieldRotate(matrixField, axis, angle);
	setScalarField(sf);
	///setVectorField(vf);
	///setMatrixField(mf);
};
