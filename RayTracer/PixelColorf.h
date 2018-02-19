#pragma once

#define BLACK PixelColorf(0.0f, 0.0f, 0.0f, 0.0f)
#define WHITE PixelColorf(1.0f, 1.0f, 1.0f, 0.0f)
#define RED PixelColorf(1.0f, 0.0f, 0.0f, 0.0f)
#define GREEN PixelColorf(0.0f, 1.0f, 0.0f, 0.0f)
#define BLUE PixelColorf(0.0f, 0.0f, 1.0f, 0.0f)

#include <iostream>
#include <math.h>

class PixelColorf {

	public:
		float R;
		float G;
		float B; 
		float A;

		PixelColorf();

		PixelColorf(float Rvalue, float Gvalue, float Bvalue, float Avalue);

		PixelColorf operator * (float k);

		PixelColorf operator + (const PixelColorf & c);

};

struct PixelColor {
	uint8_t R; //0-255
	uint8_t G;
	uint8_t B;
	uint8_t A;
};

PixelColorf operator * (float k, const PixelColorf & c);

PixelColorf intColorToFloatColor(PixelColor & i);

PixelColor floatColorToIntColor(PixelColorf & f);

std::ostream & operator << (std::ostream &os, PixelColorf &p);




