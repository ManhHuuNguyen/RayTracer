#include "Raster.h"
#include "CONSTANTS.h"

Raster::Raster(int w, int h) {
	width = w;
	height = h;
	pixels = new PixelColor[width*height];	
	zBuffer = new float[width*height];
	for (int i = 0; i < width*height; i++) {
		zBuffer[i] = -INFINITY;
	}
}

void Raster::clear() {
	PixelColor blackInt = { 0, 0, 0, 0 };
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i * width + j] = blackInt;
		}
	}
}

void Raster::draw(Scene & scene) {
	for (int i = 0; i < scene.size(); i++){
		drawTriangleArray(scene.objects[i]);
	}
}

Raster::~Raster() {
	delete[] pixels;
	delete[] zBuffer;
}

void Raster::writeToBMPFile(const char * path) {
	FILE * f = fopen(path, "wb");
	if (f == NULL) {
		printf("Couldnt open file for writing!!");
		return;
	}

	char b = 'B';
	fwrite(&b, sizeof(char), 1, f);
	char m = 'M';
	fwrite(&m, sizeof(char), 1, f);
	int fileSize = 54 + 3 * width * height;
	fwrite(&fileSize, sizeof(int), 1, f);
	char bfReserve[4] = { 0, 0, 0, 0 };
	fwrite(bfReserve, 1, 4, f);
	int bfOffbits = 54;
	fwrite(&bfOffbits, sizeof(int), 1, f);
	int biSize = 40;
	fwrite(&biSize, sizeof(int), 1, f);
	fwrite(&width, sizeof(int), 1, f);
	fwrite(&height, sizeof(int), 1, f);
	uint16_t biPlanes = 1;
	fwrite(&biPlanes, 2, 1, f);
	uint16_t biBitCount = 24;
	fwrite(&biBitCount, 2, 1, f);
	int biCompression = 0;
	fwrite(&biCompression, sizeof(int), 1, f);
	int biSizeImage = 0;
	fwrite(&biSizeImage, sizeof(int), 1, f);
	int pixelPerMeter = 0;
	fwrite(&pixelPerMeter, sizeof(int), 1, f);
	fwrite(&pixelPerMeter, sizeof(int), 1, f);
	int biClrUsed = 0;
	fwrite(&biClrUsed, sizeof(int), 1, f);
	int biClrImportant = 0;
	fwrite(&biClrImportant, sizeof(int), 1, f);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			PixelColor pixelValue = pixels[y*width+x];
			// this order may very well be wrong!!!! Remember to check this later future Manh!!!
			fwrite(&pixelValue.B, 1, 1, f);
			fwrite(&pixelValue.G, 1, 1, f);
			fwrite(&pixelValue.R, 1, 1, f);
		}
	}
	fclose(f);
}

void Raster::writeToPPMFile(const char * path) {
	FILE * f = fopen(path, "w");
	if (f == NULL) {
		printf("Couldnt open file for writing!!");
		return;
	}
	fprintf(f, "P3\n");
	fprintf(f, "%i ", width);
	fprintf(f, "%i\n", height);
	fprintf(f, "%i\n", 255);

	for (int y = height - 1; y >= 0; y--) {
		for (int x = 0; x < width; x++) {
			fprintf(f, "%i ", pixels[y*width + x].R);
			fprintf(f, "%i ", pixels[y*width + x].G);
			fprintf(f, "%i ", pixels[y*width + x].B);
		}
	}
	fclose(f);
}

void Raster::drawTriangle(Triangle3D & t, PixelColorf & colorA, PixelColorf & colorB, PixelColorf & colorC) {
	int minX = t.vertexA.x;
	int maxX = t.vertexC.x;
	int minY = t.vertexA.y;
	int maxY = t.vertexC.y;
	if (t.vertexA.x > maxX) {
		maxX = t.vertexA.x;
	}
	if (t.vertexB.x > maxX) {
		maxX = t.vertexB.x;
	}
	if (t.vertexB.x < minX) {
		minX = t.vertexB.x;
	}
	if (t.vertexC.x < minX) {
		minX = t.vertexC.x;
	}
	if (t.vertexA.y > maxY) {
		maxY = t.vertexA.y;
	}
	if (t.vertexB.y > maxY) {
		maxY = t.vertexB.y;
	}
	if (t.vertexB.y < minY) {
		minY = t.vertexB.y;
	}
	if (t.vertexC.y < minY) {
		minY = t.vertexC.y;
	}

	if (minX < 0) {
		minX = 0;
	}
	if (minY < 0) {
		minY = 0;
	}
	if (maxX >= width) {
		maxX = width-1;
	}
	if (maxY >= height) {
		maxY = height-1;
	}
	float zA = t.vertexA.z;
	float zB = t.vertexB.z;
	float zC = t.vertexC.z;
	for (int Y = minY; Y <= maxY; Y++) {
		for (int X = minX; X <= maxX; X++) {
			float lambda1;
			float lambda2;
			float lambda3;
			t.getBarycentricCoordinate(X, Y, &lambda1, &lambda2, &lambda3);
			if ((0.0f <= lambda1 && 0.0f <= lambda2 && 0.0f <= lambda3)) {
				
				float zValue = lambda1 * zA + lambda2 * zB + lambda3 * zC;
				if (abs(zValue) < abs(zBuffer[Y * width + X])) {
					// If a point is closer to the eye, which is at (0, 0, 0) then draw. Is this a problem? 
					PixelColorf interpolatedColor = lambda1 * colorA + lambda2 * colorB + lambda3 * colorC;
					pixels[Y * width + X] = floatColorToIntColor(interpolatedColor);
					zBuffer[Y * width + X] = zValue;
				}
				
			}
		}
	}
}

void Raster::drawTriangleArray(Triangle3DArray & TA) {
	PixelColorf colorA = TA.colors[0];
	PixelColorf colorB = TA.colors[1];
	PixelColorf colorC = TA.colors[2];
	for (int i = 0; i < TA.size(); i++) {
		drawTriangle(TA[i], colorA, colorB, colorC);
	}

}