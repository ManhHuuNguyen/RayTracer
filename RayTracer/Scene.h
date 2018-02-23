#pragma once
#include <vector>
#include "TriangleArray.h"
#include <string>
#include "Raster.h"
#include "Light.h"

class Scene {

	public:
		int rasterWidth, rasterHeight;
		float eyeX, eyeY, eyeZ;
		float spotX, spotY, spotZ;
		float upX, upY, upZ;
		float fov, aspect, near, far;
		Colorf ambientLight;
		Light pointLight; 
		std::vector<TriangleArray> objects;
		
		Scene();

		void addObject(TriangleArray & ta);
		
		TriangleArray & getLastObj();
		
		int size(); // size of instance member object

		void draw(Raster & raster);
};