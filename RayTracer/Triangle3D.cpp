#include "Triangle3D.h"


Triangle3D::Triangle3D() {

}

Triangle3D::Triangle3D(const Vector4f & v1, const Vector4f & v2, const Vector4f & v3) {
	vertexA = v1;
	vertexB = v2;
	vertexC = v3;
}

Triangle3D::Triangle3D(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	vertexA = Vector4f(x1, y1, z1);
	vertexB = Vector4f(x2, y2, z2);
	vertexC = Vector4f(x3, y3, z3);
}

Vector4f Triangle3D::getCentroid() {
	return Vector4f((vertexA.x + vertexB.x + vertexC.x) / 3.0f, 
					(vertexA.y + vertexB.y + vertexC.y) / 3.0f, 
					(vertexA.z + vertexB.z + vertexC.z) / 3.0f);
}

void Triangle3D::getBarycentricCoordinate(int X, int Y, float * l1, float * l2, float * l3){
	float denonimator = (float)((vertexB.y - vertexC.y) * (vertexA.x - vertexC.x) + (vertexC.x - vertexB.x) * (vertexA.y - vertexC.y));
	float lambda1 = ((vertexB.y - vertexC.y)*(X - vertexC.x) + (vertexC.x - vertexB.x)*(Y - vertexC.y)) / denonimator;
	float lambda2 = ((vertexC.y - vertexA.y)*(X - vertexC.x) + (vertexA.x - vertexC.x)*(Y - vertexC.y)) / denonimator;
	*l1 = lambda1;
	*l2 = lambda2;
	*l3 = 1 - lambda1 - lambda2;
}

std::ostream & operator << (std::ostream &os, Triangle3D & t) {
	return os << "Triangle3D<" << t.vertexA << ", " << t.vertexB << ", " << t.vertexC << ">";
}

void Triangle3D::homogenize() {
	vertexA.homogenize();
	vertexB.homogenize();
	vertexC.homogenize();
}