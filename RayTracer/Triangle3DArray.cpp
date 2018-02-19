#include "Triangle3DArray.h"

Triangle3DArray::Triangle3DArray() {

}

Triangle3D & Triangle3DArray::operator[](int index) {
	if (index >= vectTriangle.size()) {
		std::cout << "Index out of bound";
		throw;
	}
	return vectTriangle[index];
}

int Triangle3DArray::size() {
	return vectTriangle.size();
}

void Triangle3DArray::addTriangle(Triangle3D & t) {
	vectTriangle.push_back(t);
}

void Triangle3DArray::addTriangleColor(PixelColorf a, PixelColorf b, PixelColorf c) {
	colors[0] = a;
	colors[1] = b;
	colors[2] = c;
}

std::ostream & operator << (std::ostream &os, Triangle3DArray & ta) {
	os << "[" << std::endl;
	for (int i = 0; i < ta.size(); i++) {
		os << ta[i] << "," << std::endl;
	}
	os << "]" << std::endl;
	return os;
}

void Triangle3DArray::moveIntoEyeCoordinate(Matrix4x4 & cameraMatrix) {
	Matrix4x4 tm = cameraMatrix;

	for (int i = 0; i < transformations.size(); i++) {
		tm = tm * transformations[i];
	}
	for (int i = 0; i < vectTriangle.size(); i++) {
		Triangle3D t = vectTriangle[i];
		vectTriangle[i].vertexA = tm * t.vertexA;
		vectTriangle[i].vertexB = tm * t.vertexB;
		vectTriangle[i].vertexC = tm * t.vertexC;
	}
}

void Triangle3DArray::backFaceCulling() {
	for (int i = 0; i < vectTriangle.size(); i++) {
		Triangle3D t = vectTriangle[i];
		Vector4f v0 = t.vertexB - t.vertexA;
		Vector4f v1 = t.vertexC - t.vertexA;
		Vector4f normalVect = crossProduct(v0, v1);
		if (normalVect * t.vertexA > 0.0f) {
			culledTriangle++;
			vectTriangle.erase(vectTriangle.begin() + i);
		}
	}
}


void Triangle3DArray::applyMatrix(Matrix4x4 & m){
	for (int i = 0; i < vectTriangle.size(); i++) {
		Triangle3D t = vectTriangle[i];
		vectTriangle[i].vertexA = m * t.vertexA;
		vectTriangle[i].vertexB = m * t.vertexB;
		vectTriangle[i].vertexC = m * t.vertexC;
		
	}
}

void Triangle3DArray::homogenize() {
	for (int i = 0; i < vectTriangle.size(); i++) {
		vectTriangle[i].homogenize();
	}
}

