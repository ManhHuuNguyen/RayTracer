#pragma once

#include <vector>
#include "Colorf.h"
#include "Matrix4x4.h"
#include "Vector3f.h"

class TriangleArray {

	public: // does it need destructor?
		std::vector<std::vector<int>> faces;
		Colorf KaKd; // essentially color of object
		Colorf Ks; // object's shininess, specular coefficent
		std::vector<Vector4f> vertices;
		std::vector<Vector4f> vertexNormal;
		std::vector<Vector3f> vertexTexture;
		std::vector<Matrix4x4> transformations;
		std::string texture;
		int culledTriangle = 0;

		TriangleArray();

		//~TriangleArray();

		std::vector<int> operator[](int index);

		int size();
};

