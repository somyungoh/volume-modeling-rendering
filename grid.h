#ifndef _SM_GRID_H_
#define _SM_GRID_H_

/****************************************************************
*
*		grid.h
*
*		A light class.
*		Currently implemented following a point light model.
*
*		Usage:
*		- check bounding box
*		- if intersects, run eval
*
****************************************************************/

#include "field.h"
#include "gmath.h"
#include "mesh.h"
#include <string>
#include <iostream>

// ******	Base Grid Template	 ****** //

template<typename T>
class grid : public field<T>{

public:
	grid() {};
	grid(const vec3 &LLC, const vec3 &URC, int subdivX, int subdivY, int subdivZ);
	~grid() { delete[] data; };
	
	typedef T gridType;
	
	const vec3	LLC, URC;			// Lower-Left-Corner, Upper-Right-Corner(+Z dir)
	const int	subdivX, subdivY, subdivZ;	// subdivision (x,y,z)
	const float	dx, dy, dz;
	gridType	*data;

	// file I/O
	void read(std::string filename);
	void write(std::string filename);	// this is usually called by generate()
	
	// helper methods
	const float  trilinearInterpolate(const vec3 &p)		const;
	const vec3 	getWorldPositionAt(int i, int j, int k)		const; 	// computes world position at grid point g(ijk)
	void		set(int i, int j, int k, const gridType &val)	const;	// set grid value at input position
	void		set(const vec3 &p, const gridType &val)		const;
	void		add(int i, int j, int k, const gridType &val)	const;
	void		initGrid();
	virtual void 	generate() {};
};



// ********************************* //
//	grid template class definition
// ********************************* //

template<typename T>
grid<T>::grid(const vec3 &LLC, const vec3 &URC, int subdivX, int subdivY, int subdivZ)
	: LLC(LLC), URC(URC), dx((URC.x - LLC.x) / subdivX), dy((URC.y - LLC.y) / subdivY), dz((URC.z - LLC.z) / subdivZ)
	, subdivX(subdivX), subdivY(subdivY), subdivZ(subdivZ), data(new gridType[subdivX * subdivY * subdivZ]) {};

template<typename T>
void grid<T>::read(std::string filename) {

	printf("Start reading a file\n");
	std::ifstream is;
	is.open(filename);
	for (int i = 0; i < subdivX * subdivY * subdivZ; i++) { std::string temp; is >> temp; data[i] = std::stof(temp); };
	is.close();
	printf("Finished reading a file\n");
};

template<typename T>
const vec3 grid<T>::getWorldPositionAt(int i, int j, int k) const {
	return vec3(LLC.x + dx * i, LLC.y + dy * j, LLC.z + dz * k);
};

template<typename T>
void grid<T>::write(std::string filename) {

	std::ofstream os;
	os.open(filename);
	for (int i = 0; i < subdivX * subdivY * subdivZ; i++) { os << std::to_string(data[i]) + " "; }
	os.close();
	printf("Finished writing a file\n");
};

template<typename T>
void grid<T>::add(int i, int j, int k, const gridType &val) const {
	data[i + j * subdivX + k * subdivX * subdivY] += val;
};

template<typename T>
void grid<T>::set(int i, int j, int k, const gridType &val) const {
	data[i + j * subdivX + k * subdivX * subdivY] = val;
};

template<typename T>
void grid<T>::set(const vec3 &p, const gridType &val) const {

	float i = (p.x - LLC.x) / dx;
	float j = (p.y - LLC.y) / dy;
	float k = (p.z - LLC.z) / dz;

	float wi = i - std::floorf(i);	// weights
	float wj = j - std::floorf(j);
	float wk = k - std::floorf(k);

	i = std::floorf(i);
	j = std::floorf(i);
	k = std::floorf(i);

	i = i + 1 > subdivX - 1 ? subdivX - 1 : i;
	j = j + 1 > subdivY - 1 ? subdivY - 1 : j;
	k = k + 1 > subdivZ - 1 ? subdivZ - 1 : k;

	// set to grid;
	set(i, j, k, val * (1 - wi) * (1 - wj) * (1 - wk));
	set(i + 1, j, k, val * (wi)	* (1 - wj) * (1 - wk));
	set(i, j + 1, k, val * (1 - wi) * (wj) * (1 - wk));
	set(i, j, k + 1, val * (1 - wi) * (1 - wj) * (wk));
	set(i + 1, j + 1, k, val * (wi) * (wj) * (1 - wk));
	set(i + 1, j, k + 1, val * (wi) * (1 - wj) * (wk));
	set(i, j + 1, k + 1, val * (1 - wi) * (wj) * (wk));
	set(i + 1, j + 1, k + 1, val * (wi) * (wj) * (wk));
};

template<typename T>
void grid<T>::initGrid(){
	for (int i = 0; i < subdivX * subdivY * subdivZ; i++) data[i] = gridType(0);
};

template<typename T>
const float grid<T>::trilinearInterpolate(const vec3 &p) const {

	// check boundary intersection
	if (!(p.x > LLC.x && p.x <URC.x		// x bound
		&& p.y > LLC.y && p.y < URC.y	// y bound
		&& p.z > LLC.z && p.z < URC.z))	// z bound
		return gridType(0);				// no intersection

	// interpolation - equation from Wikipedia
	int i = std::floorf((p.x - LLC.x) / dx);
	int j = std::floorf((p.y - LLC.y) / dy);
	int k = std::floorf((p.z - LLC.z) / dz);

	// set local position
	vec3 xp = p - LLC;

	if (i + 1 >= subdivX || i < 0 || j + 1 >= subdivY || j < 0 || k + 1 >= subdivZ || k < 0) return gridType(0);

	// gijk
	float g000 = data[(i)+(j)* subdivX + (k)* subdivX * subdivY];	// LLC
	float g100 = data[(i + 1) + (j)* subdivX + (k)* subdivX * subdivY];
	float g001 = data[(i)+(j)* subdivX + (k + 1) * subdivX * subdivY];
	float g101 = data[(i + 1) + (j)* subdivX + (k + 1) * subdivX * subdivY];
	float g010 = data[(i)+(j + 1) * subdivX + (k)* subdivX * subdivY];
	float g110 = data[(i + 1) + (j + 1) * subdivX + (k)* subdivX * subdivY];
	float g011 = data[(i)+(j + 1) * subdivX + (k + 1) * subdivX * subdivY];
	float g111 = data[(i + 1) + (j + 1) * subdivX + (k + 1) * subdivX * subdivY];	// URC
	float wi   = (p.x - LLC.x) / dx - i;	// weights
	float wj   = (p.y - LLC.y) / dy - j;
	float wk   = (p.z - LLC.z) / dz - k;

	// interpolation
	float g =
		g000 * (1 - wi) * (1 - wj)	* (1 - wk) +
		g100 * (wi)		* (1 - wj)	* (1 - wk) +
		g010 * (1 - wi) * (wj)		* (1 - wk) +
		g001 * (1 - wi) * (1 - wj)	* (wk)	   +
		g110 * (wi)		* (wj)		* (1 - wk) +
		g101 * (wi)		* (1 - wj)	* (wk)	   +
		g011 * (1 - wi) * (wj)		* (wk)	   +
		g111 * (wi)		* (wj)		* (wk);

	return g;
};

#endif // !_SM_GRID_H_
