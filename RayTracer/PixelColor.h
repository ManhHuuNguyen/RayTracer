
#pragma once

#define BLACK PixelColor(0, 0, 0, 0)
#define WHITE PixelColor(255, 255, 255, 0)
#define RED PixelColor(255, 0, 0, 0)
#define GREEN PixelColor(0, 255, 0, 0)
#define BLUE PixelColor(0, 0, 255, 0)

#include <iostream>

class PixelColor {

	public:
		uint8_t R; //0-255
		uint8_t G;
		uint8_t B;
		uint8_t A;

		PixelColor();

		PixelColor(int Rvalue, int Gvalue, int Bvalue, int Avalue);

		PixelColor operator * (float k);

		PixelColor operator + (const PixelColor & c);
	
};


PixelColor operator * (float k, const PixelColor & c);
std::ostream & operator << (std::ostream &os, PixelColor &p); 

