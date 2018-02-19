#include <stdio.h>
#include <iostream>
#include <string>
#include "Raster.h"
#include "Helper.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Scene.h"
#include "Triangle3DArray.h"
#include <time.h>

using namespace std;

int main(int argc, const char * argv[]) {
	int close;
	const clock_t begin_time = clock();
  	vector<string> geometry;
	Scene scene = readSceneFile("scene.u3d");
	scene.applyGraphicPipeLine();
	Raster raster(scene.rasterWidth, scene.rasterHeight);
	raster.draw(scene);
	raster.writeToPPMFile("image.ppm");
	raster.writeToBMPFile("image41.bmp");
	cout << "Number of seconds it takes: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
    std::cout << "Enter st to exit: ";
	std::cin >> close;
	return 0;
}

