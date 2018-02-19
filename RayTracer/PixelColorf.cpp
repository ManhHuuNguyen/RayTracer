#include "PixelColorf.h"

PixelColorf::PixelColorf() {

}

PixelColorf::PixelColorf(float Rvalue, float Gvalue, float Bvalue, float Avalue) {
	R = Rvalue;
	G = Gvalue;
	B = Bvalue;
	A = Avalue;
}

PixelColorf PixelColorf::operator * (float k) {
	return PixelColorf(k*R, k*G, k*B, k*A);

}

PixelColorf PixelColorf::operator + (const PixelColorf & c) {
	return PixelColorf(R + c.R, G + c.G, B + c.B, A + c.A);
}

PixelColorf operator * (float k, const PixelColorf & c) {
	return PixelColorf(k * c.R, k * c.G, k *c.B, k *c.A);
}
std::ostream & operator << (std::ostream &os, PixelColorf & p) {
	return os << "PixelColorf<" << p.R << ", " << p.G << ", " << p.B << ", " << p.A << ">";
}

PixelColorf intColorToFloatColor(PixelColor & i) {
	return PixelColorf(i.R/255.0f, i.G/255.0f, i.B/255.0f, i.A/255.0f);
}

PixelColor floatColorToIntColor(PixelColorf & f) {
	PixelColor i;
	i.R = (uint8_t)floorf(f.R >= 1.0 ? 255 : f.R*256.0f);
	i.G = (uint8_t)floorf(f.G >= 1.0 ? 255 : f.G*256.0f);
	i.B = (uint8_t)floorf(f.B >= 1.0 ? 255 : f.B*256.0f);
	i.A = (uint8_t)floorf(f.A >= 1.0 ? 255 : f.A*256.0f);
	return i;
}