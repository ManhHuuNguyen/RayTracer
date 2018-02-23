#pragma once

#include "Colorf.h"
#include <iostream>
#include <fstream>
#include "TriangleArray.h"

class Raster {

	public:

		int width; 
		int height;
		PixelColor * pixels;
		float * zBuffer;
		
		Raster(int width, int height);

		void writeToBMPFile(const char * path);
		
		void writeToPPMFile(const char * path);

		void clear();

		~Raster();
};

void getBarycentricCoordinate(Vector4f & v1, Vector4f & v2, Vector4f & v3, int X, int Y, float * l1, float * l2, float * l3);

