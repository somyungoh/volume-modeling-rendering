#ifndef SM_MESH_H_
#define SM_MESH_H_
/***********************************************************
*
*	mesh.h
*
*	A mesh object that is generated by reading OBJ file.
*	
*	About [vertexIndices, uvIndices, normalIndices]
*	Stores index of v, uv, n for each faces.
*	That is, 3 neighboring points refers to same face.
*	(i.e. vi[0], vi[1], vi[2] refers to same face)
*
*
************************************************************/
#include "field.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "gmath.h"

class scalarFieldMesh : public field<float>{
public:
	// constructors
	scalarFieldMesh();
	scalarFieldMesh(const std::string &file_name, const std::string &file_path);
	~scalarFieldMesh();

	const fieldType eval(const vec3 &p) const;
	//const gradType  grad(const vec3 &p) const;
	
	// getters, setters
	const bool  load_objFile(const std::string &file_name, const std::string &file_path);
	
private:
	// data storage
	std::vector<int>  vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> vertices;
	std::vector<vec3> uvs;
	std::vector<vec3> normals;
};

#endif // !SM_MESH_H_