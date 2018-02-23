#pragma once
#include "Vector4f.h"
#include "Colorf.h"

class Light {

	public:
		Vector4f position;
		Colorf LdLs; // Ld and Ls, intensity
		Light();
		Light(float x, float y, float z, float r, float g, float b);
};