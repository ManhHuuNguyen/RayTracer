#include <stdio.h>
#include <iostream>
#include <string>
#include "Raster.h"
#include "Helper.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Scene.h"
#include "TriangleArray.h"
#include <time.h>

using namespace std;

void generateWalkAroundScene(Scene & scene, Raster & raster);

int main(int argc, const char * argv[]) {
	int close;
	const clock_t begin_time = clock();
  	vector<string> geometry;
	Scene scene = readSceneFile("scene.u3d");
	Raster raster(scene.rasterWidth, scene.rasterHeight);
	generateWalkAroundScene(scene, raster);
	/*cout << "Number of seconds reading file: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
	const clock_t begin_time1 = clock();
	scene.draw(raster);
	cout << "Number of seconds drawing 3D world: " << float(clock() - begin_time1) / CLOCKS_PER_SEC << endl;
	raster.writeToPPMFile("image.ppm");
	raster.writeToBMPFile("image.bmp");*/
    std::cout << "Enter st to exit: ";
	std::cin >> close;
	return 0;
}


void generateWalkAroundScene(Scene & scene, Raster & raster) {
	int numberOfScenes = 40;
	float R = 5.0f; 
	for (int i = 0; i < numberOfScenes; i++) {
		raster.clear();
		string fileName = "./animations/a" + to_string(i) + ".bmp";
		float alpha = 2 * PI * (float) i / numberOfScenes;
		float sinAlpha = sinf(alpha);
		float cosAlpha = cosf(alpha);
		scene.eyeX = sinAlpha*R;
		scene.eyeZ = cosAlpha*R;
		scene.draw(raster);
		raster.writeToBMPFile(fileName.c_str());
	}
}

