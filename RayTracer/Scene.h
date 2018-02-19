#pragma once
#include <vector>
#include "Triangle3DArray.h"
#include <string>

class Scene {

	public:
		int rasterWidth, rasterHeight;
		Matrix4x4 cameraMatrix;
		Matrix4x4 projectionMatrix;
		Matrix4x4 viewportMatrix;
		std::vector<Triangle3DArray> objects;
		
		Scene();

		void addObject(Triangle3DArray & ta);
		
		Triangle3DArray & getLastObj();
		
		int size(); // size of instance member object

		void applyGraphicPipeLine();

		void applyGraphicPipeLine2();
};