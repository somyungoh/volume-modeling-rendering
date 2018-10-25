#ifndef _SM_SCENE_H_
#define _SM_SCENE_H_

/******************************************************
*
*		scene.h
*
*		A scene class that stores all the fields
*
******************************************************/

#include "shape.h"
#include "mesh.h"
#include "grid.h"
#include "fieldAlgebra.h"
#include "scalarField.h"
#include "scalarGrid.h"
#include "csg.h"
#include "light.h"
#include <vector>

class scene{
public:
	// constructors
	scene();
	~scene();

	// Main eval funtion
	void eval(const vec3 &p, float &density, color &c);

	// initialization method
	void init();

	// getter, setters
	void	addShape(shape* object);
	shape*	getShape(int index);	// might not need these anymore
	light*	getLight(int index);
	int		shapeSize() const;
	int		lightSize() const;
	bool	isUsingDSM();
	void	useDSM(bool a);
	void    getNoiseParameters(Noise_t& parameters) const;
	void    setNoiseParameters(const Noise_t& parameters);

private:

	bool	usingDSM;
	
	// vector that stores vector
	std::vector<shape*> shapes;
	std::vector<light*> lights;

	// local initialize methods
	void setModel();	// do modeling
	void setLight();	// set lights
	void setGrid();		// set grids
};

#endif // !_SM_SCENE_H_