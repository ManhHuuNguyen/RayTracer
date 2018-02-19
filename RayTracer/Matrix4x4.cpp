#include "Matrix4x4.h"

Matrix4x4::Matrix4x4() {

}

Matrix4x4::Matrix4x4(float e11, float e21, float e31, float e41,
				     float e12, float e22, float e32, float e42,
					 float e13, float e23, float e33, float e43,
					 float e14, float e24, float e34, float e44) {
	this->e11 = e11; this->e21 = e21; this->e31 = e31; this->e41 = e41;
	this->e12 = e12; this->e22 = e22; this->e32 = e32; this->e42 = e42;
	this->e13 = e13; this->e23 = e23; this->e33 = e33; this->e43 = e43;
	this->e14 = e14; this->e24 = e24; this->e34 = e34; this->e44 = e44;
}

Matrix4x4 Matrix4x4::operator * (float k) {
	return Matrix4x4(k*e11, k*e21, k*e31, k*e41,
					 k*e12, k*e22, k*e32, k*e42,
					 k*e13, k*e23, k*e33, k*e43,
					 k*e14, k*e24, k*e34, k*e44);
}

Matrix4x4 Matrix4x4::operator / (float k) {
	return Matrix4x4(e11/k, e21/k, e31/k, e41/k,
					 e12/k, e22/k, e32/k, e42/k,
					 e13/k, e23/k, e33/k, e43/k,
					 e14/k, e24/k, e34/k, e44/k);
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4 & m) {
	float c11 = e11 * m.e11 + e21 * m.e12 + e31 * m.e13 + e41 * m.e14;
	float c21 = e11 * m.e21 + e21 * m.e22 + e31 * m.e23 + e41 * m.e24;
	float c31 = e11 * m.e31 + e21 * m.e32 + e31 * m.e33 + e41 * m.e34;
	float c41 = e11 * m.e41 + e21 * m.e42 + e31 * m.e43 + e41 * m.e44;

	float c12 = e12 * m.e11 + e22 * m.e12 + e32 * m.e13 + e42 * m.e14;
	float c22 = e12 * m.e21 + e22 * m.e22 + e32 * m.e23 + e42 * m.e24;
	float c32 = e12 * m.e31 + e22 * m.e32 + e32 * m.e33 + e42 * m.e34;
	float c42 = e12 * m.e41 + e22 * m.e42 + e32 * m.e43 + e42 * m.e44;

	float c13 = e13 * m.e11 + e23 * m.e12 + e33 * m.e13 + e43 * m.e14;
	float c23 = e13 * m.e21 + e23 * m.e22 + e33 * m.e23 + e43 * m.e24;
	float c33 = e13 * m.e31 + e23 * m.e32 + e33 * m.e33 + e43 * m.e34;
	float c43 = e13 * m.e41 + e23 * m.e42 + e33 * m.e43 + e43 * m.e44;

	float c14 = e14 * m.e11 + e24 * m.e12 + e34 * m.e13 + e44 * m.e14;
	float c24 = e14 * m.e21 + e24 * m.e22 + e34 * m.e23 + e44 * m.e24;
	float c34 = e14 * m.e31 + e24 * m.e32 + e34 * m.e33 + e44 * m.e34;
	float c44 = e14 * m.e41 + e24 * m.e42 + e34 * m.e43 + e44 * m.e44;

	return Matrix4x4(c11, c21, c31, c41,
					 c12, c22, c32, c42,
					 c13, c23, c33, c43,
					 c14, c24, c34, c44);

}

Vector4f Matrix4x4::operator * (const Vector4f & V) {
	float x = e11 * V.x + e21 * V.y + e31 * V.z + e41 * V.w;
	float y = e12 * V.x + e22 * V.y + e32 * V.z + e42 * V.w;
	float z = e13 * V.x + e23 * V.y + e33 * V.z + e43 * V.w;
	float w = e14 * V.x + e24 * V.y + e34 * V.z + e44 * V.w;
	return Vector4f(x, y, z, w);
}

void Matrix4x4::identityMatrix() {

	e11 = 1.0f; e21 = 0.0f; e31 = 0.0f; e41 = 0.0f;
	e12 = 0.0f, e22 = 1.0f; e32 = 0.0f; e42 = 0.0f;
	e13 = 0.0f; e23 = 0.0f; e33 = 1.0f; e43 = 0.0f;
	e14 = 0.0f; e24 = 0.0f; e34 = 0.0f; e44 = 1.0f;
}

Matrix4x4 operator *(float k, const Matrix4x4 & m) {
	return Matrix4x4(k*m.e11, k*m.e21, k*m.e31, k*m.e41,
			 		 k*m.e12, k*m.e22, k*m.e32, k*m.e42,
					 k*m.e13, k*m.e23, k*m.e33, k*m.e43,
					 k*m.e14, k*m.e24, k*m.e34, k*m.e44);

}

std::ostream & operator << (std::ostream &os, Matrix4x4 &m) {
	return os << "Matrix4x4<" << m.e11 << ", " << m.e21 << ", " << m.e31 << ", " << m.e41 << "\n          "
							  << m.e12 << ", " << m.e22 << ", " << m.e32 << ", " << m.e42 << "\n          "
							  << m.e13 << ", " << m.e23 << ", " << m.e33 << ", " << m.e43 << "\n          "
							  << m.e14 << ", " << m.e24 << ", "	<< m.e34 << ", " << m.e44 << ">";
}

Matrix4x4 scaleMatrix(float sx, float sy, float sz) {
	return Matrix4x4(  sx, 0.0f, 0.0f, 0.0f,
					 0.0f,   sy, 0.0f, 0.0f,
					 0.0f, 0.0f,   sz, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f
		);
}

Matrix4x4 translationMatrix(float tx, float ty, float tz) {
	return Matrix4x4(1.0f, 0.0f, 0.0f, tx,
					 0.0f, 1.0f, 0.0f, ty,
					 0.0f, 0.0f, 1.0f, tz,
					 0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 rotationMatrixAboutX(float theta) {
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	return Matrix4x4(1.0f,	   0.0f,	  0.0f, 0.0f, 
					 0.0f, cosTheta, -sinTheta, 0.0f,
					 0.0f, sinTheta,  cosTheta, 0.0f,
					 0.0f,     0.0f,      0.0f, 1.0f);
}


Matrix4x4 rotationMatrixAboutY(float theta) {
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	return Matrix4x4(cosTheta, 0.0f, sinTheta, 0.0f,
						 0.0f, 1.0f,	 0.0f, 0.0f,
					-sinTheta, 0.0f, cosTheta, 0.0f,
					     0.0f, 0.0f,     0.0f, 1.0f);
}

Matrix4x4 rotationMatrixAboutZ(float theta) {
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	return Matrix4x4(cosTheta, -sinTheta, 0.0f, 0.0f, 
					 sinTheta,  cosTheta, 0.0f, 0.0f,
					     0.0f,      0.0f, 1.0f, 0.0f,
						 0.0f,      0.0f, 0.0f, 1.0f
		);
}

Matrix4x4 rotationMatrixAboutRandAxis(Vector4f N, float theta) {
	N.normalize();
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	float oneMinusCosTheta = 1.0f - cosTheta;
	float x = N.x;
	float y = N.y;
	float z = N.z;
	float a11 = x * x * oneMinusCosTheta + cosTheta;
	float a21 = x * y * oneMinusCosTheta - z * sinTheta;
	float a31 = x * z * oneMinusCosTheta + y * sinTheta;

	float a12 = x * y * oneMinusCosTheta + z * sinTheta;
	float a22 = y * y * oneMinusCosTheta + cosTheta;
	float a32 = y * z * oneMinusCosTheta - x * sinTheta;

	float a13 = x * z * oneMinusCosTheta - y * sinTheta;	
	float a23 = y * z * oneMinusCosTheta + x * sinTheta;
	float a33 = z * z * oneMinusCosTheta + cosTheta;
	return Matrix4x4(a11,   a21,  a31, 0.0f,
					 a12,   a22,  a32, 0.0f,
					 a13,   a23,  a33, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 cameraMatrix(Vector4f & eyeVect, Vector4f & spotVect, Vector4f & upVect) {
	Vector4f look = spotVect - eyeVect;
	look.normalize();
	Vector4f right = crossProduct(look, upVect);
	right.normalize();
	
	Vector4f up = crossProduct(right, look);
	
	look.normalize();
	right.normalize();
	up.normalize();

	float rx = right.x, ry = right.y, rz = right.z;
	float ux = up.x, uy = up.y, uz = up.z;
	float lx = look.x, ly = look.y, lz = look.z;
	float ex = eyeVect.x, ey = eyeVect.y, ez = eyeVect.z;
	return Matrix4x4(
		  rx,   ry,   rz, -rx * ex - ry * ey - rz * ez,
		  ux,   uy,   uz, -ux * ex - uy * ey - uz * ez,
		 -lx,  -ly,  -lz,  lx * ex + ly * ey + lz * ez,
		0.0f, 0.0f,  0.0f,                        1.0f
	);
}

Matrix4x4 orthoProjectionMatrix(float l, float r, float b, float t, float n, float f) {
	return Matrix4x4(
		2.0f/(r - l),    0.0f,       0.0f,   (r + l)/(l - r),
		        0.0f, 2/(t-b),       0.0f,       (t+b)/(b-t),
		        0.0f,    0.0f, 2.0f/(n-f),       (f+n)/(n-f),
		        0.0f,    0.0f,       0.0f,              1.0f
	);
}

Matrix4x4 viewportMatrix(float w, float h) {
	return Matrix4x4(w/2.0f,   0.0f, 0.0f, w/2.0f,
					   0.0f, h/2.0f, 0.0f, h/2.0f,
					   0.0f,   0.0f, 1.0f,   0.0f, // shouldnt this be 0? but if it is, I dont have any info to do z-buffering
		               0.0f,   0.0f, 0.0f,   1.0f);
}

Matrix4x4 frustumMatrix(float l, float r, float b, float t, float n, float f) {
	return Matrix4x4(
		2*n/(r-l),      0.0f,  (r+l)/(r-l),         0.0f,
		     0.0f, 2*n/(t-b),  (t+b)/(t-b),         0.0f,
		     0.0f,      0.0f, -(f+n)/(f-n), -2*f*n/(f-n),
		     0.0f,      0.0f,        -1.0f,         0.0f
	);
}

Matrix4x4 perspectiveProjectionMatrix(float fovy, float a, float n, float f) {
	float tangent = tanf(fovy/2);
	float deltaZ = f - n;
	return Matrix4x4(
		1/(tangent * a),        0.0f,          0.0f,          0.0f,
		           0.0f,   1/tangent,          0.0f,          0.0f,
		           0.0f,        0.0f, -(f+n)/deltaZ, -2*n*f/deltaZ,
		           0.0f,        0.0f,         -1.0f,          0.0f
	);
}