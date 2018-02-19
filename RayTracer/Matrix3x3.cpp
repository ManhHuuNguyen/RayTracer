#include "Matrix3x3.h"


Matrix3x3::Matrix3x3() {
	e11 = 1.0f; e21 = 0.0f; e31 = 0.0f;
	e12 = 0.0f; e22 = 1.0f; e32 = 0.0f;
	e13 = 0.0f; e23 = 0.0f; e33 = 1.0f;
}

Matrix3x3::Matrix3x3(float e11, float e21, float e31,
					 float e12, float e22, float e32,
					 float e13, float e23, float e33) {
	this->e11 = e11; this->e21 = e21; this->e31 = e31;
	this->e12 = e12; this->e22 = e22; this->e32 = e32;
	this->e13 = e13; this->e23 = e23; this->e33 = e33;
}

Matrix3x3 Matrix3x3::operator * (float k) {
	return Matrix3x3(k*e11, k*e21, k*e31,
					 k*e12, k*e22, k*e32,
				     k*e13, k*e23, k*e33);
}

Matrix3x3 Matrix3x3::operator / (float k) {

	return Matrix3x3(e11/k, e21/k, e31/k,
					 e12/k, e22/k, e32/k,
					 e13/k, e23/k, e33/k);
}

float Matrix3x3::getDeterminant() {
	return e11*e22*e33 + e21*e32*e13 + e31*e12*e23 - e31*e22*e13 - e21*e12*e33 - e11*e32*e23;
}

void Matrix3x3::identityMatrix() {
	e11 = 1.0f; e21 = 0.0f; e31 = 0.0f;
	e12 = 0.0f; e22 = 1.0f; e32 = 0.0f;
	e13 = 0.0f; e23 = 0.0f; e33 = 1.0f;
}


Matrix3x3 Matrix3x3::operator * (const Matrix3x3 & m) { 
	float a11 = e11 * m.e11 + e21 * m.e12 + e31 * m.e13;
	float a21 = e11 * m.e21 + e21 * m.e22 + e31 * m.e23;
	float a31 = e11 * m.e31 + e21 * m.e32 + e31 * m.e33;

	float a12 = e12 * m.e11 + e22 * m.e12 + e32 * m.e13;
	float a22 = e12 * m.e21 + e22 * m.e22 + e32 * m.e23;
	float a32 = e12 * m.e31 + e22 * m.e32 + e32 * m.e33;

	float a13 = e13 * m.e11 + e23 * m.e12 + e33 * m.e13;
	float a23 = e13 * m.e21 + e23 * m.e22 + e33 * m.e23;
	float a33 = e13 * m.e31 + e23 * m.e32 + e33 * m.e33;

	return Matrix3x3(a11, a21, a31, 
					 a12, a22, a32, 
					 a13, a23, a33);
}


Vector3f Matrix3x3::operator * (const Vector3f & v) {
	float vx = e11 * v.x + e21 * v.y + e31 * v.z;
	float vy = e12 * v.x + e22 * v.y + e32 * v.z;
	return Vector3f(vx, vy);
}

Matrix3x3 operator *(float k, Matrix3x3 & m) {
	return Matrix3x3(k*m.e11, k*m.e21, k*m.e31, 
					 k*m.e12, k*m.e22, k*m.e32, 
					 k*m.e13, k*m.e23, k*m.e33);
}

std::ostream & operator << (std::ostream &os, Matrix3x3 &m) {
	return os << "Matrix3x3<" << m.e11 << ", " << m.e21 << ", " << m.e31 << "\n          " 
							  << m.e12 << ", " << m.e22 << ", " << m.e32 << "\n          "
						      << m.e13 << ", " << m.e23 << ", " << m.e33 << ">";
}

Matrix3x3 rotationMatrix(float theta) {
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	return Matrix3x3(
		cosTheta, -sinTheta, 0.0f,
		sinTheta,  cosTheta, 0.0f,
		    0.0f,      0.0f, 1.0f
	);

	 
}
Matrix3x3 translationMatrix(float tx, float ty) {

	return Matrix3x3(
		1.0f, 0.0f, tx,
		0.0f, 1.0f, ty,
		0.0f, 0.0f, 1.0f
	);
}
Matrix3x3 scaleMatrix(float sx, float sy) {
	return Matrix3x3(
		sx, 0.0f, 0.0f,
		0.0f, sy, 0.0f,
		0.0f, 0.0f, 1.0f
	);

}