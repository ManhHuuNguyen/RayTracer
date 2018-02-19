#pragma once

#include <math.h>
#include "Vector4f.h"
#include "CONSTANTS.h"

#define IDENTITYMATRIX4X4 Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,\
									0.0f, 1.0f, 0.0f, 0.0f,\
									0.0f, 0.0f, 1.0f, 0.0f,\
									0.0f, 0.0f, 0.0f, 1.0f)


class Matrix4x4 { // column matrix

public:
	float e11, e21, e31, e41;
	float e12, e22, e32, e42;
	float e13, e23, e33, e43;
	float e14, e24, e34, e44;

	Matrix4x4(); // construct an identity matrix

	Matrix4x4(float e11, float e21, float e31, float e41,
		      float e12, float e22, float e32, float e42,
			  float e13, float e23, float e33, float e43,
			  float e14, float e24, float e34, float e44);

	Matrix4x4 operator * (float k);

	Matrix4x4 operator / (float k);

	Matrix4x4 operator * (const Matrix4x4 & m);

	Vector4f operator * (const Vector4f & V);

	void identityMatrix();

};

Matrix4x4 operator *(float k, const Matrix4x4 & m);

std::ostream & operator << (std::ostream &os, Matrix4x4 &m);

Matrix4x4 rotationMatrixAboutX(float theta);

Matrix4x4 rotationMatrixAboutY(float theta);

Matrix4x4 rotationMatrixAboutZ(float theta);

Matrix4x4 rotationMatrixAboutRandAxis(Vector4f v, float theta);

Matrix4x4 translationMatrix(float tx, float ty, float tz);

Matrix4x4 scaleMatrix(float sx, float sy, float sz);

Matrix4x4 orthoProjectionMatrix(float l, float r, float b, float t, float n, float f);

Matrix4x4 viewportMatrix(float w, float h);

Matrix4x4 frustumMatrix(float l, float r, float b, float t, float n, float f);

Matrix4x4 perspectiveProjectionMatrix(float fovy, float a, float n, float f);

Matrix4x4 cameraMatrix(Vector4f & eyeVect, Vector4f & spotVect, Vector4f & upVect);

