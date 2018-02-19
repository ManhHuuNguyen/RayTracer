#include "Vector4f.h"

Vector4f::Vector4f() {

}

Vector4f::Vector4f(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
	w = 1.0f;
}

Vector4f::Vector4f(float X, float Y, float Z, float W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}

bool Vector4f::operator == (const Vector4f & V) {
	return abs(x - V.x) <= CLOSE_VALUE && (y - V.y) <= CLOSE_VALUE && (z - V.z) <= CLOSE_VALUE;
}

bool Vector4f::operator != (const Vector4f & V) {
	return abs(x - V.x) > CLOSE_VALUE || abs(y - V.y) > CLOSE_VALUE || (z - V.z) > CLOSE_VALUE;
}

Vector4f Vector4f::operator + (const Vector4f & V) {
	if (abs(w - V.w) > CLOSE_VALUE) {
		throw;
	}
	return Vector4f(x + V.x, y + V.y, z + V.z, w);
}

Vector4f Vector4f::operator - (const Vector4f & V) {
	if (abs(w - V.w) > CLOSE_VALUE) {
		throw;
	}
	return Vector4f(x - V.x, y - V.y, z - V.z, w);
}

Vector4f Vector4f::operator * (float a) {
	return Vector4f(a * x, a * y, a* z, w);
}

Vector4f Vector4f::operator / (float a) {
	return Vector4f(x / a, y / a, z / a, w);
}

float Vector4f::operator * (const Vector4f & V) {
	if (abs(w - V.w) > CLOSE_VALUE) {
		throw;
	}
	return x * V.x + y * V.y + z * V.z;
}

Vector4f Vector4f::operator - () {
	return Vector4f(-x, -y, -z, w);
}

void Vector4f::zero() {
	x = y = z = 0.0f;
	w = 1.0f;
}

void Vector4f::normalize() {
	float magnitude = sqrtf(x * x + y * y + z * z);
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

void Vector4f::homogenize() {
	x = x / w;
	y = y / w;
	z = z / w;
	w = w / w;
}

Vector4f operator *(float k, const Vector4f & V) {
	return Vector4f(k * V.x, k * V.y, k * V.z, V.w);
}

std::ostream & operator << (std::ostream &os, Vector4f &V) {
	return os << "Vector4f<" << V.x << ", " << V.y << ", " << V.z << ", " << V.w << ">";
}

Vector4f crossProduct(Vector4f & v1, Vector4f & v2) {
	if (abs(v1.w - v2.w) > CLOSE_VALUE) {
		throw;
	}
	return Vector4f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x, v1.w);
}