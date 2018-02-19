#pragma once

#include <vector>
#include "Triangle3D.h"
#include "PixelColorf.h"
#include "Matrix4x4.h"

class Triangle3DArray {

	public: // does it need destructor?
		std::vector<Triangle3D> vectTriangle;
		PixelColorf colors[3];
		std::vector<Matrix4x4> transformations;
		int culledTriangle = 0;

		Triangle3DArray();

		//~Triangle3DArray();

		Triangle3D & operator[](int index);

		int size();

		void addTriangle(Triangle3D & t);

		void addTriangleColor(PixelColorf a, PixelColorf b, PixelColorf c);

		void applyMatrix(Matrix4x4 & m);

		void moveIntoEyeCoordinate(Matrix4x4 & cameraMatrix);

		void homogenize();

		void backFaceCulling();
};

std::ostream & operator << (std::ostream &os, Triangle3DArray & ta);

