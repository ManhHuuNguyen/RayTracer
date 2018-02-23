#include "Scene.h"

Scene::Scene() {

}

void Scene::addObject(TriangleArray & ta) {
	objects.push_back(ta);
}

int Scene::size() {
	return objects.size();
}

TriangleArray & Scene::getLastObj() {
	return objects.back();
}

void Scene::draw(Raster & raster) {
	Vector4f eyeVect(eyeX, eyeY, eyeZ);
	Vector4f spotVect(spotX, spotY, spotZ);
	Vector4f upVect(upX, upY, upZ);
	Matrix4x4 camMatrix = cameraMatrix(eyeVect, spotVect, upVect);
	Matrix4x4 projectionMatrix = perspectiveProjectionMatrix(fov, aspect, near, far);
	Matrix4x4 viewport = viewportMatrix(rasterWidth, rasterHeight);
	
	// moving light into eye coordinate
	Vector4f lightInEyeCoor = camMatrix * pointLight.position;

	for (int k = 0; k < objects.size(); k++) {
		bool hasTexture = true;
		if (objects[k].vertexTexture.size() == 0) {
			hasTexture = false;
		}

		// move into eye coordinate
		Matrix4x4 modelViewMatrix = camMatrix;

		for (int i = 0; i < objects[k].transformations.size(); i++) {
			modelViewMatrix = modelViewMatrix * objects[k].transformations[i];
		}
		int culledTriangle = 0;
		for (int i = 0; i < objects[k].faces.size(); i++) {
			std::vector<int> face = objects[k].faces[i];
			int v1Index = face[0]; int v2Index = face[1]; int v3Index = face[2];
			int vn1Index = face[3]; int vn2Index = face[4]; int vn3Index = face[5];
			int vt1Index, vt2Index, vt3Index;
			if (hasTexture) {
				vt1Index = face[6]; vt2Index = face[7]; vt3Index = face[8];
			}
			Vector4f v1 = modelViewMatrix * objects[k].vertices[v1Index];
			Vector4f v2 = modelViewMatrix * objects[k].vertices[v2Index];
			Vector4f v3 = modelViewMatrix * objects[k].vertices[v3Index];
			// clipping against near and far plane
			/*if (objects[k].vectTriangle[i].vertexA.z > far &&
				objects[k].vectTriangle[i].vertexB.z > far &&
				objects[k].vectTriangle[i].vertexC.z > far) {
				std::cout << "culled by far" << std::endl;
				continue;
			}
			else if (objects[k].vectTriangle[i].vertexA.z < near &&
					 objects[k].vectTriangle[i].vertexB.z < near &&
					 objects[k].vectTriangle[i].vertexC.z < near) {
				std::cout << "culled by near" << std::endl;
				continue;
			}*/
			// back-face culling
			Vector4f va = v2 - v1;
			Vector4f vb = v3 - v1;
			Vector4f normalVect = crossProduct(va, vb);
			if (normalVect * v1 > 0.0f) {
				culledTriangle++;
				continue;
			}
			// saving vertices in eye coordinate for lighting purposes
			/*Vector4f eyeCoorV1 = v1; 
			Vector4f eyeCoorV2 = v2;
			Vector4f eyeCoorV3 = v3;*/
			
			// projection matrix
			v1 = projectionMatrix * v1;
			v2 = projectionMatrix * v2;
			v3 = projectionMatrix * v3;
			// homogenize
			v1.homogenize();
			v2.homogenize();
			v3.homogenize();
			// viewport matrix
			v1 = viewport * v1;
			v2 = viewport * v2;
			v3 = viewport * v3;

			//raster.drawTriangle(v1, v2, v3, objects[k].diffuseCoefficient);
			int minX = v1.x;
			int maxX = v3.x;
			int minY = v1.y;
			int maxY = v3.y;
			if (v1.x > maxX) {
				maxX = v1.x;
			}
			if (v2.x > maxX) {
				maxX = v2.x;
			}
			if (v2.x < minX) {
				minX = v2.x;
			}
			if (v3.x < minX) {
				minX = v3.x;
			}
			if (v1.y > maxY) {
				maxY = v1.y;
			}
			if (v2.y > maxY) {
				maxY = v2.y;
			}
			if (v2.y < minY) {
				minY = v2.y;
			}
			if (v3.y < minY) {
				minY = v3.y;
			}

			if (minX < 0) {
				minX = 0;
			}
			if (minY < 0) {
				minY = 0;
			}
			if (maxX >= rasterWidth) {
				maxX = rasterWidth - 1;
			}
			if (maxY >= rasterHeight) {
				maxY = rasterHeight - 1;
			}
			
			float zA = v1.z; float zB = v2.z; float zC = v3.z;
			for (int Y = minY; Y <= maxY; Y++) {
				for (int X = minX; X <= maxX; X++) {
					float lambda1, lambda2, lambda3;
					getBarycentricCoordinate(v1, v2, v3, X, Y, &lambda1, &lambda2, &lambda3);
					if ((0.0f <= lambda1 && 0.0f <= lambda2 && 0.0f <= lambda3)) {
						float zValue = lambda1 * zA + lambda2 * zB + lambda3 * zC;
						if (abs(zValue) < abs(raster.zBuffer[Y * rasterWidth + X])) {// If a point is closer to the eye, which is at (0, 0, 0) then draw.
							float lamb1, lamb2, lamb3;
							Vector4f eyeCoorV1 = modelViewMatrix * objects[k].vertices[v1Index];
							Vector4f eyeCoorV2 = modelViewMatrix * objects[k].vertices[v2Index];
							Vector4f eyeCoorV3 = modelViewMatrix * objects[k].vertices[v3Index];
							getBarycentricCoordinate(eyeCoorV1, eyeCoorV2, eyeCoorV3, X, Y, &lamb1, &lamb2, &lamb3);

							Vector4f incidentPoint = lamb1 * eyeCoorV1 + lamb2 * eyeCoorV2 + lamb3 * eyeCoorV3;
							Vector4f l = lightInEyeCoor - incidentPoint;

							Vector4f normal1 = objects[k].vertexNormal[vn1Index];
							Vector4f normal2 = objects[k].vertexNormal[vn2Index];
							Vector4f normal3 = objects[k].vertexNormal[vn3Index];
							Vector4f normal = lamb1 * normal1 + lamb2 * normal2 + lamb3 * normal3;
							l.normalize();
							normal.normalize();
							Colorf color = pointLight.LdLs * objects[k].KaKd * fmaxf(l*normal, 0.0f); // add diffuse color
							color = color + ambientLight * objects[k].KaKd; // add ambient color
							Vector4f r = 2 * (normal * l) * normal - l;
							Vector4f v = - incidentPoint; // because eye is at (0, 0, 0) in eye coordinate
							r.normalize();
							v.normalize();
							//color = color + pointLight.LdLs * objects[k].Ks * powf(fmax(r*v, 0.0f), objects[k].Ks.A);
							raster.pixels[Y * rasterWidth + X] = floatColorToIntColor(color);
							raster.zBuffer[Y * rasterWidth + X] = zValue;
						}

					}
				}
			}
		}
		std::cout << "Percent saved: " << (float)culledTriangle/objects[k].size()*100 << std::endl;
	}
}