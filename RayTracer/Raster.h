#pragma once

#include "PixelColorf.h"
#include <iostream>
#include <fstream>
#include "Helper.h"

class Raster {

	public:

		int width; 
		int height;
		PixelColor * pixels;
		float * zBuffer;
		
		Raster(int width, int height);

		void writeToBMPFile(const char * path);
		
		void writeToPPMFile(const char * path);

		void drawTriangle(Triangle3D & t, PixelColorf & colorA, PixelColorf & colorB, PixelColorf & colorC);
		
		void drawTriangleArray(Triangle3DArray & t);

		void draw(Scene & scene);

		void clear();

		~Raster();
};

