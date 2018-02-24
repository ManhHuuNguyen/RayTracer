#include "Vector3f.h"
#include "CONSTANTS.h"

Vector3f::Vector3f() {

}

Vector3f::Vector3f(float X, float Y) {
	x = X;
	y = Y;
	z = 1.0f;
}

Vector3f::Vector3f(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
}

bool Vector3f::operator == (const Vector3f & V) {
	return abs(x - V.x) <= CLOSE_VALUE && abs(y - V.y) <= CLOSE_VALUE;
}

bool Vector3f::operator != (const Vector3f & V) {
	return abs(x - V.x) > CLOSE_VALUE || abs(y - V.y) > CLOSE_VALUE;
}

Vector3f Vector3f::operator + (const Vector3f & V) {
	return Vector3f(x + V.x, y + V.y);
}

Vector3f Vector3f::operator - (const Vector3f & V) {
	return Vector3f(x - V.x, y - V.y);
}

Vector3f Vector3f::operator * (float a) {
	return Vector3f(a * x, a * y);
}

Vector3f Vector3f::operator / (float a) {
	return Vector3f(x / a, y / a);
}

float Vector3f::operator * (const Vector3f & V) {
	return x * V.x + y * V.y;
}

Vector3f Vector3f::operator - () {
	return Vector3f(-x, -y);
}

void Vector3f::normalize() {
	float magnitude = sqrtf(x * x + y * y);
	x = x / magnitude;
	y = y / magnitude;
}

Vector3f operator *(float k, const Vector3f & V) {
	return Vector3f(k * V.x, k * V.y);
}

std::ostream & operator << (std::ostream &os, Vector3f &V) {
	return os << "Vector3f<" << V.x << ", " << V.y << ", " << V.z << ">";
}
