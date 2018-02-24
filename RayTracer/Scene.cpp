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
		
		Matrix4x4 modelViewMatrix = camMatrix;
		for (int i = 0; i < objects[k].transformations.size(); i++) {
			modelViewMatrix = modelViewMatrix * objects[k].transformations[i];
		}

		if (objects[k].texture.size() == 0) { // if there is no texture
			// move into eye coordinate
			int culledTriangle = 0;
			for (int i = 0; i < objects[k].faces.size(); i++) {
				std::vector<int> face = objects[k].faces[i];
				int v1Index = face[0]; int v2Index = face[1]; int v3Index = face[2];
				int vn1Index = face[3]; int vn2Index = face[4]; int vn3Index = face[5];

				Vector4f v1 = modelViewMatrix * objects[k].vertices[v1Index];
				Vector4f v2 = modelViewMatrix * objects[k].vertices[v2Index];
				Vector4f v3 = modelViewMatrix * objects[k].vertices[v3Index];
				// back-face culling
				Vector4f va = v2 - v1;
				Vector4f vb = v3 - v1;
				Vector4f normalVect = crossProduct(va, vb);
				if (normalVect * v1 > 0.0f) {
					culledTriangle++;
					continue;
				}

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
								Vector4f eyeCoorV1 = modelViewMatrix * objects[k].vertices[v1Index];
								Vector4f eyeCoorV2 = modelViewMatrix * objects[k].vertices[v2Index];
								Vector4f eyeCoorV3 = modelViewMatrix * objects[k].vertices[v3Index];

								Vector4f incidentPoint = lambda1 * eyeCoorV1 + lambda2 * eyeCoorV2 + lambda3 * eyeCoorV3;
								Vector4f l = lightInEyeCoor - incidentPoint;

								Vector4f normal1 = modelViewMatrix * objects[k].vertexNormal[vn1Index];
								Vector4f normal2 = modelViewMatrix * objects[k].vertexNormal[vn2Index];
								Vector4f normal3 = modelViewMatrix * objects[k].vertexNormal[vn3Index];
								Vector4f normal = lambda1 * normal1 + lambda2 * normal2 + lambda3 * normal3;
								
								l.normalize();
								normal.normalize();
								Colorf color = pointLight.LdLs * objects[k].KaKd * fmaxf(l*normal, 0.0f); // add diffuse color
								color = color + ambientLight * objects[k].KaKd; // add ambient color
								Vector4f r = 2 * (normal * l) * normal - l;
								Vector4f v = -incidentPoint; // because eye is at (0, 0, 0) in eye coordinate
								r.normalize();
								v.normalize();
								color = color + pointLight.LdLs * objects[k].Ks * powf(fmax(r*v, 0.0f), objects[k].Ks.A);
								raster.pixels[Y * rasterWidth + X] = floatColorToIntColor(color);
								raster.zBuffer[Y * rasterWidth + X] = zValue;
							}

						}
					}
				}
			}
			std::cout << "Percent saved: " << (float)culledTriangle / objects[k].size() * 100 << std::endl;

		}
		else { // if there is texture
			Raster textureMap = readBitMapFile(objects[k].texture.c_str());
			// move into eye coordinate
			int culledTriangle = 0;
			for (int i = 0; i < objects[k].faces.size(); i++) {
				std::vector<int> face = objects[k].faces[i];
				int v1Index = face[0]; int v2Index = face[1]; int v3Index = face[2];
				int vn1Index = face[3]; int vn2Index = face[4]; int vn3Index = face[5];
				int vt1Index = face[6]; int vt2Index = face[7]; int vt3Index = face[8];
				
				Vector4f v1 = modelViewMatrix * objects[k].vertices[v1Index];
				Vector4f v2 = modelViewMatrix * objects[k].vertices[v2Index];
				Vector4f v3 = modelViewMatrix * objects[k].vertices[v3Index];
				
				// back-face culling
				Vector4f va = v2 - v1;
				Vector4f vb = v3 - v1;
				Vector4f normalVect = crossProduct(va, vb);
				if (normalVect * v1 > 0.0f) {
					culledTriangle++;
					continue;
				}

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
								
								Vector4f eyeCoorV1 = modelViewMatrix * objects[k].vertices[v1Index];
								Vector4f eyeCoorV2 = modelViewMatrix * objects[k].vertices[v2Index];
								Vector4f eyeCoorV3 = modelViewMatrix * objects[k].vertices[v3Index];

								Vector4f incidentPoint = lambda1 * eyeCoorV1 + lambda2 * eyeCoorV2 + lambda3 * eyeCoorV3;
								Vector4f l = lightInEyeCoor - incidentPoint;

								Vector4f normal1 = modelViewMatrix * objects[k].vertexNormal[vn1Index];
								Vector4f normal2 = modelViewMatrix * objects[k].vertexNormal[vn2Index];
								Vector4f normal3 = modelViewMatrix * objects[k].vertexNormal[vn3Index];
								Vector4f normal = lambda1 * normal1 + lambda2 * normal2 + lambda3 * normal3;

								l.normalize();
								normal.normalize();

								Vector3f vTexture1 = objects[k].vertexTexture[vt1Index];
								Vector3f vTexture2 = objects[k].vertexTexture[vt2Index];
								Vector3f vTexture3 = objects[k].vertexTexture[vt3Index];

								Vector3f currentTexture = lambda1 * vTexture1 + lambda2 * vTexture2 + lambda3 * vTexture3;
								int tx = (int)(currentTexture.x * textureMap.width);
								int ty = (int)(currentTexture.y * textureMap.height);

								Colorf colorAtPixel = intColorToFloatColor(
									textureMap.pixels[ty * textureMap.width + tx]);

								Colorf color = pointLight.LdLs * colorAtPixel * fmaxf(l*normal, 0.0f); // add diffuse color
								color = color + ambientLight * colorAtPixel; // add ambient color
								Vector4f r = 2 * (normal * l) * normal - l;
								Vector4f v = -incidentPoint; // because eye is at (0, 0, 0) in eye coordinate
								r.normalize();
								v.normalize();
								color = color + pointLight.LdLs * objects[k].Ks * powf(fmax(r*v, 0.0f), objects[k].Ks.A);
								raster.pixels[Y * rasterWidth + X] = floatColorToIntColor(color);
								raster.zBuffer[Y * rasterWidth + X] = zValue;
							}

						}
					}
				}
			}
			std::cout << "Percent saved: " << (float)culledTriangle / objects[k].size() * 100 << std::endl;
		}
		
		
	}
}

Raster readBitMapFile(const char * path) {
	int i;
	FILE* f = fopen(path, "rb");

	if (f == NULL)
		throw "Argument Exception";

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

											   // extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	Raster raster(width, height);

	for (int i = 0; i < height; i++){
		
		for (int j = 0; j < width * 3; j += 3){
			// Convert (B, G, R) to (R, G, B)
			uint8_t blue;
			fread(&blue, 1, 1, f);
			//uint8_t blue = data;
			uint8_t green;
			fread(&green, 1, 1, f);
			uint8_t red;
			fread(&red, 1, 1, f);
			raster.pixels[i * width + j/3] = PixelColor{red, green, blue, 0};
		}
	}
	fclose(f);
	return raster;
}