#include "Scene.h"

Scene::Scene() {

}

void Scene::addObject(Triangle3DArray & ta) {
	objects.push_back(ta);
}

int Scene::size() {
	return objects.size();
}

Triangle3DArray & Scene::getLastObj() {
	return objects.back();
}

void Scene::applyGraphicPipeLine() {
	for (int k = 0; k < objects.size(); k++) {
		/*std::cout << "Starting coordinate: " << std::endl;
		std::cout << objects[k] << std::endl;*/

		objects[k].moveIntoEyeCoordinate(cameraMatrix);
		/*std::cout << "Moving into eye coordinate: " << std::endl;
		std::cout << objects[k] << std::endl;*/

		objects[k].backFaceCulling();

		std::cout << "Percent saved: " << (float)objects[k].culledTriangle / objects[k].vectTriangle.size() * 100 << "%" << std::endl;

		objects[k].applyMatrix(projectionMatrix);
		/*std::cout << "Applying perspective projection: " << std::endl;
		std::cout << objects[k] << std::endl;*/

		objects[k].homogenize();
		/*std::cout << "Homogenizing: " << std::endl;
		std::cout << objects[k] << std::endl;*/

		objects[k].applyMatrix(viewportMatrix);
		/*std::cout << "To viewport coordinate: " << std::endl;
		std::cout << objects[k] << std::endl;*/
	}

}

void Scene::applyGraphicPipeLine2() {
	for (int k = 0; k < objects.size(); k++) {

		// move into eye coordinate
		Matrix4x4 m = IDENTITYMATRIX4X4;
		m = m * cameraMatrix;

		for (int i = 0; i < objects[k].transformations.size(); i++) {
			m = m * objects[k].transformations[i];
		}

		
		int culledTriangle = 0;
		for (int i = 0; i < objects[k].vectTriangle.size(); i++) {
			objects[k].vectTriangle[i].vertexA = m * objects[k].vectTriangle[i].vertexA;
			objects[k].vectTriangle[i].vertexB = m * objects[k].vectTriangle[i].vertexB;
			objects[k].vectTriangle[i].vertexC = m * objects[k].vectTriangle[i].vertexC;
			// back-face culling
			Vector4f v0 = objects[k].vectTriangle[i].vertexB - objects[k].vectTriangle[i].vertexA;
			Vector4f v1 = objects[k].vectTriangle[i].vertexC - objects[k].vectTriangle[i].vertexA;
			Vector4f normalVect = crossProduct(v0, v1);
			if (normalVect * objects[k].vectTriangle[i].vertexA > 0.0f) {
				culledTriangle++;
				continue;
			}
			// projection matrix
			objects[k].vectTriangle[i].vertexA = projectionMatrix * objects[k].vectTriangle[i].vertexA;
			objects[k].vectTriangle[i].vertexB = projectionMatrix * objects[k].vectTriangle[i].vertexB;
			objects[k].vectTriangle[i].vertexC = projectionMatrix * objects[k].vectTriangle[i].vertexC;
			// homogenize
			objects[k].vectTriangle[i].vertexA.homogenize();
			objects[k].vectTriangle[i].vertexB.homogenize();
			objects[k].vectTriangle[i].vertexC.homogenize();
			// viewport matrix
			objects[k].vectTriangle[i].vertexA = viewportMatrix * objects[k].vectTriangle[i].vertexA;
			objects[k].vectTriangle[i].vertexB = viewportMatrix * objects[k].vectTriangle[i].vertexB;
			objects[k].vectTriangle[i].vertexC = viewportMatrix * objects[k].vectTriangle[i].vertexC;
		}
		std::cout << "Percent saved: " << (float)culledTriangle/objects[k].size()*100 << std::endl;
	}
}