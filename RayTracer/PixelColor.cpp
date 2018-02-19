#include "PixelColor.h"

PixelColor::PixelColor() {

}

PixelColor::PixelColor(int Rvalue, int Gvalue, int Bvalue, int Avalue) {
	R = Rvalue;
	G = Gvalue;
	B = Bvalue;
	A = Avalue;
}

PixelColor PixelColor::operator * (float k) { // this causes loss of precision. might need to rewrite
	return PixelColor((int)(k*R), (int)(k*G), (int)(k*B), (int)(k*A));
}

PixelColor PixelColor::operator + (const PixelColor & c) {
	return PixelColor(R + c.R, G + c.G, B + c.B, A + c.A);
}

PixelColor operator * (float k, const PixelColor & c) { // this causes loss of precision. might need to rewrite later
	return PixelColor((int) (k * c.R), (int)(k * c.G), (int)(k *c.B), (int)(k *c.A));
}

std::ostream & operator << (std::ostream &os, PixelColor &p) {
	return os << "PixelColor<" << (unsigned)p.R << ", " << (unsigned)p.G << ", " << (unsigned)p.B << ", " << (unsigned)p.A << ">";
}
