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
	for (int i = 0; i < width*height; i++) {
		zBuffer[i] = -INFINITY;
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

void getBarycentricCoordinate(Vector4f & v1, Vector4f & v2, Vector4f & v3, int X, int Y, float * l1, float * l2, float * l3) {
	float denonimator = (float)((v2.y - v3.y) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.y - v3.y));
	float lambda1 = ((v2.y - v3.y)*(X - v3.x) + (v3.x - v2.x)*(Y - v3.y)) / denonimator;
	float lambda2 = ((v3.y - v1.y)*(X - v3.x) + (v1.x - v3.x)*(Y - v3.y)) / denonimator;
	*l1 = lambda1;
	*l2 = lambda2;
	*l3 = 1 - lambda1 - lambda2;
}