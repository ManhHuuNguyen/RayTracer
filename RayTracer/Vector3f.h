#pragma once
#include <math.h>
#include <string>


class Vector3f {

public:
	float x;
	float y;
	float z;

	Vector3f();

	Vector3f(float X, float Y);

	bool operator == (const Vector3f & V);

	bool operator != (const Vector3f & V);

	Vector3f operator + (const Vector3f & V);

	Vector3f operator - (const Vector3f & V);

	Vector3f operator * (float a);

	Vector3f operator / (float a);

	float operator * (const Vector3f & V);

	Vector3f operator - ();

	void zero();

	void normalize();

};

Vector3f operator *(float k, const Vector3f & V);

std::ostream & operator << (std::ostream &os, Vector3f &V);

