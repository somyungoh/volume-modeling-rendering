/****************************************************************
*
*		Somyung(David) Oh
*
*		Project4
*
*		Volume Modeling and Rendering (VIZA 689)
*		2018 Spring, Texas A&M University
*		Instructor - Dr.Jerry Tessendorf
*
*		*For MSVC project settings,
*		 do C/C++ > Preprocessor > Preprocessor definitions
*		 Add:
*		 _CRT_SECURE_NO_WARNINGS - for safe stdlib issues
*		 NDEBUG					 - for strange freeglut error
*
****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "render.h"
#include "GL\freeglut.h"
#include "OpenEXR\ImfRgbaFile.h"

//******************************//
//		Gloabal Constants		//
//******************************//

// image size
#define WIDTH	580
#define HEIGHT	540

render	renderer;
float*	pixmap;
int		frameCount;
bool	isRendering;

std::ofstream ofs;		// parameter output
Noise_t param;

// WISP
float inc_octave = 4.f / 19;	// f/500
float inc_freq = 7.f / 8;	// f/10
float inc_fjmp = 0.5f / 5;	// f/5
float inc_clump = 8 / 7.2;	// f/11

// NOISE
//float inc_octave = 4.f / 23;	// f/500
//float inc_freq = 7.f / 8;	// f/10
//float inc_fjmp = 0.5f / 5;	// f/5
//float inc_fall = 8 / 7.2;	// f/11

// PYROSPHERES
//float inc_octave = 4.f / 500;	// f/500
//float inc_freq	 = 7.f / 10;	// f/10
//float inc_fjmp	 = 0.5f / 5;	// f/5
//float inc_gam	 = 1.f / 11;	// f/11

//******************************//
//		save - openEXR			//
//******************************//
void saveEXR() {

	// copy colors into openEXR rgba buffer
	
	Imf::Rgba *pixelBuffer = new Imf::Rgba[WIDTH * HEIGHT];
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			
			int index = y * WIDTH + x;

			pixelBuffer[index].r = pixmap[index * 4 + 0];
			pixelBuffer[index].g = pixmap[index * 4 + 1];
			pixelBuffer[index].b = pixmap[index * 4 + 2];
			pixelBuffer[index].a = pixmap[index * 4 + 3];
		}
	}

	// set file name
	frameCount++;
	std::stringstream os; os << frameCount;
	std::string dispframe = os.str();
	if (frameCount < 1000) { dispframe = "0" + dispframe; }
	if (frameCount < 100)  { dispframe = "0" + dispframe; }
	if (frameCount < 10)   { dispframe = "0" + dispframe; }
	std::string fname = std::string("Render/render") + "." + dispframe;

	// write file
	Imf::RgbaOutputFile file(std::string(fname + std::string(".exr")).c_str(), WIDTH, HEIGHT, Imf::WRITE_RGBA);
	file.setFrameBuffer(pixelBuffer, 1, WIDTH);
	file.writePixels(HEIGHT);

	// write .csv file
	ofs << "frame," << frameCount << ",octaves," << param.octaves + 1 << ",freq," << param.frequency + 1 << ",fjump," << param.fjump + 2 << ",clump," << param.clump << std::endl;

	std::cout << "Main::image saved - frame" << frameCount - 1 << std::endl;

	// deallocate buffer
	delete[] pixelBuffer;
};


//******************************//
//		GLUT Routine			//
//******************************//

// idle func
void idle() {

}


// keyboard input funtion
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
		saveEXR();
		break;
	case 'r':
		if (isRendering) { isRendering = false; std::cout << "Main::stop rendering" << std::endl; }
		else { isRendering = true; std::cout << "Main::start turntable rendering" << std::endl; }
		glutPostRedisplay();
		break;
	default:
		break;
	}

	//glutPostRedisplay();		// redraw
}


// arrowkey input
void arrowkey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		renderer.moveIn(0.1f);
		break;

	case GLUT_KEY_DOWN:
		renderer.moveOut(0.1f);
		break;

	case GLUT_KEY_LEFT:
		renderer.rotate(-5.f);
		break;

	case GLUT_KEY_RIGHT:
		renderer.rotate(5.f);
		break;

	default:
		break;
	}

	glutPostRedisplay();		// redraw
}


// resize function
void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (w / 2), 0, (h / 2), 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// display function
void display() {
	
	renderer.run(pixmap);

	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	glDrawPixels(WIDTH, HEIGHT, GL_RGBA, GL_FLOAT, pixmap);
	glutSwapBuffers();

	if (isRendering) {
		saveEXR();

		// update parameters
		//renderer.rotate(3.f);
		
		// NOISE
		if (frameCount % 11 == 0) param.octaves = inc_octave + param.octaves;
		param.frequency = param.frequency + inc_freq;
		if (frameCount % 11 == 0)  param.frequency = 0;
		if (frameCount % 22 == 0)  param.fjump = std::fmod(param.fjump + inc_fjmp, 3.5);
		param.clump = param.clump * inc_clump;
		if (frameCount % 11 == 0) param.clump = 0;

		// PYROSPHERE
		//if (frameCount % 22 == 0) param.octaves = inc_octave + param.octaves;
		//if(frameCount % 11 == 0)  param.frequency = std::fmod(param.frequency + inc_freq, 8) + 1;
		//if(frameCount % 33 == 0)  param.fjump	  = std::fmod(param.fjump + inc_fjmp, 2.5) + 2;	
		//param.gamma		= param.gamma - inc_gam;
		//if (param.gamma < 0.5) param.gamma = 1.5;

		renderer.setNoiseParameters(param);

		glutPostRedisplay();
	}
}


// print controls
void printUsage() {

	std::cout << "------------------------------------------------------------------------------\n" << std::endl;
	std::cout << "\t Project2 - Volume Rendering, Fall 2018, Texas A&M University" << std::endl;
	std::cout << "\t Made by Somyung (David) Oh.\n" << std::endl;
	std::cout << "\t Keyboard Controls:" << std::endl;
	std::cout << "\t [r] \ttoogle turntable rendering" << std::endl;
	std::cout << "\t [s] \tsave current image" << std::endl;
	std::cout << "\t [arrow] move camera" << std::endl;
	std::cout << "\n-----------------------------------------------------------------------------\n" << std::endl;
}


// initialize everything
void init() {

	pixmap		= new float[WIDTH * HEIGHT * 4];
	renderer	= render(WIDTH, HEIGHT);
	frameCount	= 0;
	isRendering = true;

	ofs.open("parameter.csv");

	// initialize noise parameter
	param.octaves	= 0;
	param.frequency = 0;
	param.fjump		= 0;
	param.clump		= 0;
	
	//param.roughness = 0.5;
	//param.amplitude = 1.0;
	//param.clump		= 1;
	//param.falloff	= 1;
	//renderer.setNoiseParameters(param);

	printUsage();
}



//	Main Function
int main(int argc, char* argv[]){

	// initizalize program
	init();

	//	GLUT Initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);

	//	GLUT Display
	glutCreateWindow("VIZA689::Project3");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowkey);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	//glutIdleFunc(idle);
	
	glutMainLoop();

	return 0;
}
