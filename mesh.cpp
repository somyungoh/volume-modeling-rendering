#include "mesh.h"

/*********************************************************
*
*		mesh.cpp
*
*		Implementation of a mesh class
*		This class stores obj files
*
**********************************************************/
using namespace std;

// constructors
scalarFieldMesh::scalarFieldMesh() {};
scalarFieldMesh::scalarFieldMesh(const std::string &file_name, const std::string &file_path) { load_objFile(file_name, file_path); };
scalarFieldMesh::~scalarFieldMesh() {};


// finds closest point(target) from desired point(from, dir)
// this is used in scene class, when generating level sets
// precondition: origin(from), direction(dir), result(target)
const scalarFieldMesh::fieldType scalarFieldMesh::eval(const vec3 &p) const {

	// steps:
	// 1) find closest point on a plane
	// 2) if NO, find closest point on edges or vertices
	float minDistance = -100000;
	vec3  closestPoint;
	int   intersection = 0;

	// run ray - triangle intersection test for all faces
	for (int i = 0; i < vertexIndices.size() / 3; i++) {
		
		// 1. prepare vertices
		vec3 v0 = vertices[vertexIndices[i * 3 + 0]];
		vec3 v1 = vertices[vertexIndices[i * 3 + 1]];
		vec3 v2 = vertices[vertexIndices[i * 3 + 2]];
		
		vec3 edge1 = v1 - v0;
		vec3 edge2 = v2 - v0;

		vec3 e12 = glm::cross(edge1, edge2);
		vec3 e21 = glm::cross(edge2, edge1);
		vec3 n   = glm::normalize(e12);
		vec3 r   = (p - v0) - n * glm::dot(n, p - v0);

		float uu = glm::dot(glm::cross(edge2, r), e21) / glm::dot(e12, e12);
		float vv = glm::dot(glm::cross(edge1, r), e12) / glm::dot(e12, e12);

		// 1. check first conditinjon - plane intersection 
		// IF NOT INTERSECT, perfrom nearest point on edge
		//if (uu < 0.0 || uu > 1.0 || vv < 0.0 || uu + vv > 1.0) {
		if (uu < 0.0 || uu > 1.0 || vv < 0.0 || vv > 1.0 || uu + vv > 1.0 || uu + vv < 0.0) {
			
			//continue;	// skip if no intersection with plane

			// initialize ratio factors
			vec3 edge3 = v2 - v1;	// we didn't set this yet
			
			// calculate closest points
			// ratio qn on edges
			float q1 = glm::dot(edge1, p - v0) / glm::dot(edge1, edge1);
			float q2 = glm::dot(edge2, p - v0) / glm::dot(edge2, edge2);
			float q3 = glm::dot(edge3, p - v1) / glm::dot(edge3, edge3);
			
			// points pn
			vec3  p1 = v0 + q1 * edge1;
			vec3  p2 = v0 + q2 * edge2;
			vec3  p3 = v1 + q3 * edge3;
			
			// distance dn to each points
			float d1 = glm::length(p1 - p) * (glm::dot(normals[normalIndices[i * 3 + 0]], p1 - p) > 0 ? 1 : -1);
			float d2 = glm::length(p2 - p) * (glm::dot(normals[normalIndices[i * 3 + 0]], p2 - p) > 0 ? 1 : -1);
			float d3 = glm::length(p3 - p) * (glm::dot(normals[normalIndices[i * 3 + 2]], p3 - p) > 0 ? 1 : -1);

			// 2. check second condition - closest point on edges or vertices
			// get the minimum magnitude distance value
			bool qualify = false;
			if(q1 <= 1 && q1 >= 0) {		// stick to edge1
				if (glm::abs(d1) < glm::abs(minDistance)) { minDistance = d1; closestPoint = p1; }
				qualify = true;
			}
			if(q2 <= 1 && q2 >= 0) {		// stick to edge2
				if (glm::abs(d2) < glm::abs(minDistance)) { minDistance = d2; closestPoint = p2; }
				qualify = true;
			}
			if(q3 <= 1 && q3 >= 0) {		// stick to edge3
				if (glm::abs(d3) < glm::abs(minDistance)) { minDistance = d3; closestPoint = p3; }
				qualify = true;
			}

			// 3. Did not find minimum distance to the edge
			//	  Stick to minimum closest point
			if (!qualify) {
				float dv0 = glm::length(v0 - p) * (glm::dot(normals[normalIndices[i * 3 + 0]], v0 - p) > 0 ? 1 : -1);
				float dv1 = glm::length(v1 - p) * (glm::dot(normals[normalIndices[i * 3 + 1]], v1 - p) > 0 ? 1 : -1);
				float dv2 = glm::length(v2 - p) * (glm::dot(normals[normalIndices[i * 3 + 2]], v2 - p) > 0 ? 1 : -1);
				
				if (std::abs(dv0) < std::abs(minDistance)) { minDistance = dv0; }//minDistance = dv0; closestPoint = v0; }
				if (std::abs(dv1) < std::abs(minDistance)) { minDistance = dv1; }//minDistance = dv1; closestPoint = v1; }
				if (std::abs(dv2) < std::abs(minDistance)) { minDistance = dv2; }//minDistance = dv2; closestPoint = v2; }
			}
			// move to the next face
			continue;
		};
		
		// Passed all qualification for triangle - intersection

		// interpolate normals from file
#ifdef INTERPOLATE_NORMAL
		vec3 n0 = normals[normalIndices[i * 3 + 0]];
		vec3 n1 = normals[normalIndices[i * 3 + 1]];
		vec3 n2 = normals[normalIndices[i * 3 + 2]];
		n = (1 - uu - vv) * n0 + uu * n1 + vv * n2;		// Phong Shading
		
		// interpolate uv from file
		//vec2 uv0 = uvs[uvIndices[i * 3 + 0]];
		//vec2 uv1 = uvs[uvIndices[i * 3 + 1]];
		//vec2 uv2 = uvs[uvIndices[i * 3 + 2]];
		//vec2 uv = (1 - uu - vv) * uv0 + uu * uv1 + vv * uv2;
		//float u = uv.x;
		//float v = uv.y;
#endif // INTERPOLATE_NORMAL

		//printf("stick to plane!\n");

		// compute min point / distance
		float thisDistance = glm::dot(n, v0 + uu * edge1 + vv * edge2 - p);
		if (glm::abs(thisDistance) < glm::abs(minDistance))
			minDistance = thisDistance;
		
		intersection++;
	}	// end of the vertex-loop
	
	return minDistance;
};


/*************************************************************************************
*
*	Object Loader
*
*	Implementation of a object loading funtion.
*
*	this code is written from
*	http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*
**************************************************************************************/
const bool scalarFieldMesh::load_objFile(const string &file_name, const string &file_path) {

	FILE *file = fopen(string(file_path + "/" + file_name).c_str(), "r");	// open file
																			///ifstream file(file_path + "/" + file_name);
	int num_vertices = 0;
	int num_faces = 0;

	if (file == NULL) {														// check failure
		cout << "OBJLOAD::File loading failed." << endl;
		return false;
	}
	cout << "OBJLOAD::Start loading OBJ: " << file_name << endl;

	int loop_count = 0;

	while (1) {			// loop until the end of the file

		// 1. read header

		char lineHeader[128];		// header, such as v, vt, vn ....
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)				// stop reading if EOF
			break;

		// 2. parse with headers

		// v - vertex
		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
			num_vertices++;
		}
		// vt - UV texture position
		else if (strcmp(lineHeader, "vt") == 0) {
			vec3 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		// vn - vertex normal
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		// f - faces
		else if (strcmp(lineHeader, "f") == 0) {
			int v_index[3], uv_index[3], n_index[3];

			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v_index[0], &uv_index[0], &n_index[0],
				&v_index[1], &uv_index[1], &n_index[1],
				&v_index[2], &uv_index[2], &n_index[2]);
			
			if (matches != 9) {				// file format did not match to the reader
				cout << "OBJLOAD::Face format - v/vt/n did not match." << endl;
				return false;
			}

			vertexIndices.push_back(v_index[0] - 1);		// - 1, because obj file starts index with 1.
			vertexIndices.push_back(v_index[1] - 1);
			vertexIndices.push_back(v_index[2] - 1);
			uvIndices.push_back(uv_index[0] - 1);
			uvIndices.push_back(uv_index[1] - 1);
			uvIndices.push_back(uv_index[2] - 1);
			normalIndices.push_back(n_index[0] - 1);
			normalIndices.push_back(n_index[1] - 1);
			normalIndices.push_back(n_index[2] - 1);

			num_faces++;
			loop_count++;
		}

	}	// end of while() - reading file
	
	cout << "OBJLOAD::OBJ Load Complete.\tvertices: " << num_vertices << "\tfaces: " << num_faces << endl;
};

