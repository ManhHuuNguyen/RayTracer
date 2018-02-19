#include "Helper.h"


std::vector<std::string> splitString(std::string str) {
	std::vector<std::string> vect;
	std::string substring;
	for (char & c : str) {
		if (c == ' ' || c == '\n'){
			if (substring != "") {
				vect.push_back(substring);
				substring.clear();
			}
		}
		else {
			substring += c;
		}
	}
	if (substring != "") {
		vect.push_back(substring);
	}
	return vect;
}




std::vector<Triangle3D> readRawFile(const char * path) {
	std::vector<Triangle3D> triangleArr;
	std::ifstream f(path);
	if (!f) {
		std::cout << "Cannot open raw file" << std::endl;
		throw;
	}
	std::string str;
	int count = 0;
	float coordinates[9];
	std::vector<std::string> line;
	while (getline(f, str)) {
		line = splitString(str);
		for (int i = 0; i < line.size(); i++) {
			coordinates[count] = strtof(line[i].c_str(), 0);
			count++;
			
			if (count == 9) {
				Triangle3D triangle(coordinates[0], coordinates[1], coordinates[2],
								    coordinates[3], coordinates[4], coordinates[5],
								    coordinates[6], coordinates[7], coordinates[8]);
				triangleArr.push_back(triangle);
				count = 0;
			}
		}
	}
	f.close();
	return triangleArr;
}

Scene readSceneFile(const char * path) {
	std::vector<std::string> geometry;
	std::ifstream f(path);
	if (!f) {
		std::cout << "Cannot open scene file" << std::endl;
		throw;
	}
	Scene scene;
	std::string str = "\n";
	std::getline(f, str);
	std::vector<std::string> vect = splitString(str);
	if (vect[0] != "U3") {
		throw;
	}
	getline(f, str); // get width and height of raster
	vect = splitString(str); 
	scene.rasterWidth = atoi(vect[0].c_str());
	scene.rasterHeight = atoi(vect[1].c_str());
	scene.viewportMatrix = viewportMatrix(scene.rasterWidth, scene.rasterHeight);

	getline(f, str); // get eye coordinate
	vect = splitString(str);
	Vector4f eye(strtof(vect[0].c_str(), 0), strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0));
	getline(f, str); // get spot coordinate
	vect = splitString(str);
	Vector4f spot(strtof(vect[0].c_str(), 0), strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0));
	getline(f, str); // get up coordinate
	vect = splitString(str);
	Vector4f up(strtof(vect[0].c_str(), 0), strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0));
	scene.cameraMatrix = cameraMatrix(eye, spot, up);

	getline(f, str);
	vect = splitString(str);
	scene.projectionMatrix = perspectiveProjectionMatrix(strtof(vect[0].c_str(), 0), 
		strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0));


	while (getline(f, str)) {
		vect = splitString(str);
		if (vect.size() > 0) {
			if (vect[0] == "g") {
				Triangle3DArray a = Triangle3DArray();
				geometry.push_back(vect[1]);
				scene.addObject(a);
			}
			else if (vect[0] == "c") {
				scene.getLastObj().colors[0] = PixelColorf(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0), 0);
				scene.getLastObj().colors[1] = PixelColorf(strtof(vect[4].c_str(), 0), strtof(vect[5].c_str(), 0), strtof(vect[6].c_str(), 0), 0);
				scene.getLastObj().colors[2] = PixelColorf(strtof(vect[7].c_str(), 0), strtof(vect[8].c_str(), 0), strtof(vect[9].c_str(), 0), 0);
			}
			else if (vect[0] == "t") {
				Matrix4x4 m = translationMatrix(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0));
				scene.getLastObj().transformations.push_back(m);
			}
			else if (vect[0] == "r") {
				Vector4f v(strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0), strtof(vect[4].c_str(), 0));
				Matrix4x4 m = rotationMatrixAboutRandAxis(v, strtof(vect[1].c_str(), 0));
				scene.getLastObj().transformations.push_back(m);
			}
			else if (vect[0] == "s") {
				Matrix4x4 m = scaleMatrix(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0));
				scene.getLastObj().transformations.push_back(m);
			}
		}
	}
	f.close();
	// add vertex info to triangle array
	for (int i = 0; i < scene.size(); i++) {
		//std::vector<Triangle3D> ta = readRawFile(geometry[i].c_str());
		std::vector<Triangle3D> ta = readObjFile(geometry[i].c_str());
		scene.objects[i].vectTriangle = ta;
	}
	return scene;
}

std::vector<Triangle3D> readObjFile(const char * path) {
	std::vector<Triangle3D> triangleArr; 
	std::vector<Vector4f> vertices;
	std::ifstream f(path);
	if (!f) {
		std::cout << "Cannot open scene file" << std::endl;
		throw;
	}
	
	std::string str;
	while (getline(f, str)) {
		std::vector<std::string> vect = splitString(str);
		if (vect[0] == "v") {
			Vector4f v(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0));
			vertices.push_back(v);
		}
		else if (vect[0] == "f") {
			std::string vertexA = vect[1];
			std::string vertexB = vect[2];
			std::string vertexC = vect[3];
			int vertexAIndex = atoi(splitStringWithDelimiter(vertexA, '/')[0].c_str());
			int vertexBIndex = atoi(splitStringWithDelimiter(vertexB, '/')[0].c_str());
			int vertexCIndex = atoi(splitStringWithDelimiter(vertexC, '/')[0].c_str());
			Triangle3D triangle(vertices[vertexAIndex-1], vertices[vertexBIndex-1], vertices[vertexCIndex-1]);
			triangleArr.push_back(triangle);
		}
	}
	return triangleArr;
}

std::vector<std::string> splitStringWithDelimiter(std::string str, char c) {
	std::vector<std::string> vect;
	std::string substring;
	for (char & character : str) {
		if (character == c) {
			if (substring != "") {
				vect.push_back(substring);
				substring.clear();
			}
		}
		else {
			substring += character;
		}
	}
	if (substring != "") {
		vect.push_back(substring);
	}
	return vect;
}