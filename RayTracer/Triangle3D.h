#pragma once

#include "Vector4f.h"
#include "Matrix4x4.h"

class Triangle3D {

public:
	Vector4f vertexA;
	Vector4f vertexB;
	Vector4f vertexC;

	Triangle3D();

	Triangle3D(const Vector4f & v1, const Vector4f & v2, const Vector4f & v3);

	Triangle3D(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

	void getBarycentricCoordinate(int X, int Y, float * l1, float * l2, float * l3);

	Vector4f getCentroid();

	void homogenize();
};

std::ostream & operator << (std::ostream &os, Triangle3D & t);


