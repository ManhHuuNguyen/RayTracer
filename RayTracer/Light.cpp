#include "Light.h"

Light::Light() {
}

Light::Light(float x, float y, float z, float r, float g, float b) {
	LdLs = Colorf(r, g, b, 0.0f);
	position = Vector4f(x, y, z);
}