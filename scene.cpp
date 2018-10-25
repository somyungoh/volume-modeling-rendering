#include "scene.h"

/******************************************************
*
*		scene.cpp
*
*		A scene class that stores all the shapes
*		OBJECT MODELING is done in this class
*
*
*		***** HOW TO CREATE A SCENE *****
*		
*		0) Creating a level with a object
*
******************************************************/

// constructors
scene::scene()  {}
scene::~scene() {}

// getter, setters
void	scene::addShape(shape* object)	{ shapes.push_back(object); };
shape*	scene::getShape(int i)			{ return shapes[i]; };
light*	scene::getLight(int i)			{ return lights[i]; };
int		scene::shapeSize() const		{ return shapes.size(); };
int		scene::lightSize() const		{ return lights.size(); };
bool	scene::isUsingDSM()				{ return usingDSM; };
void	scene::useDSM(bool a)			{ usingDSM = a; };

// collect eval() data from all the fields
// then return to the renderer
void scene::eval(const vec3 &p, float &d, color &c) {
	
	//initialize
	color comp(0, 0, 0, 0);
	float density = 0.0f;

	// collect eval()
	for (int i = 0; i < shapes.size(); i++) {
		float val = shapes[i]->getScalarField()->eval(p);
		density += (val < 0 ? 0 : val);
		
		comp += shapes[i]->Color() / (float)shapes.size();
	}
	// pass back
	d = density;
	c = comp;
};


// ******	initialize scene	****** //	
void scene::init() {
	
	usingDSM = false;

	setLight();
	setModel();
	setGrid();
}


// sub method of init()
// setup lights
void scene::setLight() {

	color pink_cocktail(1, 0.305, 0.313, 1);
	color heart_orange(0.985, 0.568, 0.227, 1);
	color above_yellow(0.971, 0.831, 0.137, 1);
	color blue_green(0.27, 0.678, 0.658, 1);

	color love_red(0.815, 0.0941, 0.2117, 1);
	color love_orange(0.972, 0.349, 0.192, 1);
	color love_yellow(0.929, 0.349, 0.725, 1);
	color love_green(0.639, 0.662, 0.725, 0.2823);
	color love_blue(0, 0.6, 0.725, 0.537);
	color love_purple(0.364, 0.2549, 0.341, 0.537);

	lights.push_back(new light(vec3(-0.5, 0.5, -1.3), love_blue, 1.f));
	lights.push_back(new light(vec3(0.9, -0.3, 1.0), love_yellow, 1.f));
	//lights.push_back(new light(vec3(-0.8, 0.25, 1), color(0.89, 0.98, 0.76, 1), 1.f));
}


// sub method of init()
// perform modeling steps
void scene::setModel() {

	// BUNNY
	//gridScalarPtr bunnyGrid = new scalarGrid(vec3(-1, -1, -1), vec3(1, 1, 1), 50, 50, 50);
	//bunnyGrid->read("Grids/bunnyGrid.txt");
	//shape* shapeBunny = new shape(color(0.678, 0.27, 0.658, 1));
	//shapeBunny->setScalarField(bunnyGrid);

	// PYROSPHERE
	//fieldScalarPtr sphere = new scalarFieldPyroclasticSphere(vec3(0, 0, 0), 0.8);
	//shape* shapeSphere = new shape(color(1, 1, 1, 1));
	//shapeSphere->setScalarField(sphere); 

	// NOISE
	//fieldScalarPtr sphere = new scalarFieldSphere(vec3(0, 0, 0), 1);
	//fieldScalarPtr wisp = new scalarFieldNoise(vec3(0, 0, 0));
	//shape* shapeWisp = new shape(color(1, 1, 1, 1));
	//shapeWisp->setScalarField(wisp);

	// register all the shapes into the scene
	//shapes.push_back(shapeWisp);
}

void scene::setGrid() {
	
	Noise_t param;
	param.octaves = 1.0;
	param.frequency = 1.0;
	param.fjump = 2.0;
	param.clump = 0.5;

	Noise_t param2;
	param2.octaves = 1.0;
	param2.frequency = 1.0;
	param2.fjump = 2.0;
	param2.clump = 0.5;

	fieldScalarPtr wisp = new scalarGridWISP(vec3(-1, -1, -1), vec3 (1, 1, 1), 500, 500, 500);
	dynamic_cast<scalarGridWISP*>(wisp)->generate(param, param2, 5000000, "test");

	// register to the scene
	shape* shapeWisp = new shape(color(1, 1, 1, 1));
	shapeWisp->setScalarField(wisp);
	shapes.push_back(shapeWisp);
}


// ***** TEMPORARY METHODS FOR PROJECT3 ***** //
void  scene::getNoiseParameters(Noise_t& parameters) const 
{ dynamic_cast<scalarFieldNoise*>(shapes.front()->getScalarField())->getNoiseParameters(parameters); };
void  scene::setNoiseParameters(const Noise_t& parameters) 
{ 
	// this means that its rendering a new one
	if (!shapes.empty()){
		dynamic_cast<scalarGridWISP*>(shapes.back()->getScalarField())->clearMemory();
		shapes.pop_back();
	}
	Noise_t param1, param2;

	param1.octaves = 1.0 + parameters.octaves;
	param1.frequency = 1.0 + parameters.frequency;
	param1.fjump = 2.0 + parameters.fjump;
	param1.clump = 0.5 + parameters.clump;

	param2.octaves = 1.0 + 0.5 * parameters.octaves;
	param2.frequency = 1.0 + 0.5 * parameters.frequency;
	param2.fjump = 2.0 + 0.5 * parameters.fjump;
	param2.clump = 0.5 + 0.5 * parameters.clump;

	// create wisp
	fieldScalarPtr wisp = new scalarGridWISP(vec3(-1, -1, -1), vec3(1, 1, 1), 500, 500, 500);
	dynamic_cast<scalarGridWISP*>(wisp)->generate(param1, param2, 5000000, "test");

	// register to the scene
	shape* shapeWisp = new shape(color(1, 1, 1, 1));
	shapeWisp->setScalarField(wisp);
	shapes.push_back(shapeWisp);
};