#include "Colorf.h"

Colorf::Colorf() {

}

Colorf::Colorf(float Rvalue, float Gvalue, float Bvalue, float Avalue) {
	R = Rvalue;
	G = Gvalue;
	B = Bvalue;
	A = Avalue;
}

Colorf Colorf::operator * (float k) {
	return Colorf(k*R, k*G, k*B, k*A);
}

Colorf Colorf::operator * (const Colorf & c) {
	return Colorf(c.R*R, c.G*G, c.B*B, c.A*A);
}

Colorf Colorf::operator + (const Colorf & c) {
	return Colorf(R + c.R, G + c.G, B + c.B, A + c.A);
}

Colorf operator * (float k, const Colorf & c) {
	return Colorf(k * c.R, k * c.G, k *c.B, k *c.A);
}
std::ostream & operator << (std::ostream &os, Colorf & p) {
	return os << "PixelColorf<" << p.R << ", " << p.G << ", " << p.B << ", " << p.A << ">";
}

Colorf intColorToFloatColor(PixelColor & i) {
	return Colorf(i.R/255.0f, i.G/255.0f, i.B/255.0f, i.A/255.0f);
}

PixelColor floatColorToIntColor(Colorf & f) {
	PixelColor i;
	i.R = (uint8_t)floorf(f.R >= 1.0 ? 255 : f.R*256.0f);
	i.G = (uint8_t)floorf(f.G >= 1.0 ? 255 : f.G*256.0f);
	i.B = (uint8_t)floorf(f.B >= 1.0 ? 255 : f.B*256.0f);
	i.A = (uint8_t)floorf(f.A >= 1.0 ? 255 : f.A*256.0f);
	return i;
}