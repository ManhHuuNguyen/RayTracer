#pragma once

#define BLACK Colorf(0.0f, 0.0f, 0.0f, 0.0f)
#define WHITE Colorf(1.0f, 1.0f, 1.0f, 0.0f)
#define RED Colorf(1.0f, 0.0f, 0.0f, 0.0f)
#define GREEN Colorf(0.0f, 1.0f, 0.0f, 0.0f)
#define BLUE Colorf(0.0f, 0.0f, 1.0f, 0.0f)

#include <iostream>
#include <math.h>

class Colorf {

	public:
		float R;
		float G;
		float B; 
		float A;

		Colorf();

		Colorf(float Rvalue, float Gvalue, float Bvalue, float Avalue);

		Colorf operator * (float k);

		Colorf operator * (const Colorf & c);

		Colorf operator + (const Colorf & c);

};

struct PixelColor {
	uint8_t R; //0-255
	uint8_t G;
	uint8_t B;
	uint8_t A;
};

Colorf operator * (float k, const Colorf & c);

Colorf intColorToFloatColor(PixelColor & i);

PixelColor floatColorToIntColor(Colorf & f);

std::ostream & operator << (std::ostream &os, Colorf &p);




