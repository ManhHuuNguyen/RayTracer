#pragma once
#include <math.h>
#include <string>
#include "CONSTANTS.h"

class Vector4f {

public:
	float x;
	float y;
	float z;
	float w;

	Vector4f();

	Vector4f(float X, float Y, float Z);

	Vector4f(float X, float Y, float Z, float W);

	bool operator == (const Vector4f & V);

	bool operator != (const Vector4f & V);

	Vector4f operator + (const Vector4f & V);

	Vector4f operator - (const Vector4f & V);

	Vector4f operator * (float a);

	Vector4f operator / (float a);

	float operator * (const Vector4f & V);

	Vector4f operator - ();

	void zero();

	void normalize();

	void homogenize();
};

Vector4f operator *(float k, const Vector4f & V);

std::ostream & operator << (std::ostream &os, Vector4f &V);

Vector4f crossProduct(Vector4f & v1, Vector4f & v2);

