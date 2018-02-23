#include "TriangleArray.h"

TriangleArray::TriangleArray() {

}

std::vector<int> TriangleArray::operator[](int index) {
	if (index >= faces.size()) {
		std::cout << "Index out of bound";
		throw;
	}
	return faces[index];
}

int TriangleArray::size() {
	return faces.size();
}




