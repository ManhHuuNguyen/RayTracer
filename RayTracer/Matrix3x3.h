#pragma once

#include <math.h>
#include "Vector3f.h"
#include "CONSTANTS.h"

#define IDENTITYMATRIX3X3 Matrix3x3(1.0f, 0.0f, 0.0f, \
									0.0f, 1.0f, 0.0f, \
									0.0f, 0.0f, 1.0f)



class Matrix3x3 { // column matrix

	public:
		float e11, e21, e31;
		float e12, e22, e32;
		float e13, e23, e33;

		Matrix3x3(); // construct an identity matrix

		Matrix3x3(float e11, float e21, float e31, 
				  float e12, float e22, float e32, 
				  float e13, float e23, float e33);

		Matrix3x3 operator * (float k);

		Matrix3x3 operator / (float k);

		Matrix3x3 operator * (const Matrix3x3 & m);

		Vector3f operator * (const Vector3f & V);

		void identityMatrix();

		float getDeterminant(); 

};

Matrix3x3 operator *(float k, const Matrix3x3 & m);

std::ostream & operator << (std::ostream &os, Matrix3x3 &m);

Matrix3x3 rotationMatrix(float theta);

Matrix3x3 translationMatrix(float tx, float ty);

Matrix3x3 scaleMatrix(float sx, float sy);
