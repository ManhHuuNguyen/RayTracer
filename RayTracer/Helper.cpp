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

	getline(f, str); // get eye coordinate
	vect = splitString(str);
	scene.eyeX = strtof(vect[0].c_str(), 0);
	scene.eyeY = strtof(vect[1].c_str(), 0);
	scene.eyeZ = strtof(vect[2].c_str(), 0);
	
	getline(f, str); // get spot coordinate
	vect = splitString(str);
	scene.spotX = strtof(vect[0].c_str(), 0);
	scene.spotY = strtof(vect[1].c_str(), 0);
	scene.spotZ = strtof(vect[2].c_str(), 0);

	getline(f, str); // get up coordinate
	vect = splitString(str);
	scene.upX = strtof(vect[0].c_str(), 0);
	scene.upY = strtof(vect[1].c_str(), 0);
	scene.upZ = strtof(vect[2].c_str(), 0);

	getline(f, str); // get frustum info
	vect = splitString(str);
	scene.fov = strtof(vect[0].c_str(), 0);
	scene.aspect = strtof(vect[1].c_str(), 0);
	scene.near = strtof(vect[2].c_str(), 0);
	scene.far = strtof(vect[3].c_str(), 0);

	getline(f, str); // get ambient light
	vect = splitString(str);
	scene.ambientLight = Colorf(strtof(vect[0].c_str(), 0), strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), 0.0f);

	while (getline(f, str)) {
		vect = splitString(str);
		if (vect.size() > 0) {
			if (vect[0] == "g") {
				TriangleArray a = TriangleArray();
				geometry.push_back(vect[1]);
				scene.addObject(a);
			}
			else if (vect[0] == "c") {
				scene.getLastObj().KaKd = Colorf(strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0), strtof(vect[4].c_str(), 0), strtof(vect[1].c_str(), 0));
			}

			else if (vect[0] == "p") {
				scene.getLastObj().Ks = Colorf(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0), strtof(vect[4].c_str(), 0));
			}

			else if (vect[0] == "m") {
				scene.getLastObj().texture = vect[1];
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

			else if (vect[0] == "l") {
				Light light(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0), 
					strtof(vect[4].c_str(), 0), strtof(vect[5].c_str(), 0), strtof(vect[6].c_str(), 0));
				scene.pointLight = light;
			}
		}
	}
	f.close();
	 //add vertex info to triangle array
	for (int i = 0; i < scene.size(); i++) {
		readObjFile(geometry[i].c_str(), scene.objects[i]);
	}
	return scene;
}

void readObjFile(const char * path, TriangleArray & arr) {
	std::ifstream f(path);
	if (!f) {
		std::cout << "Cannot open scene file" << std::endl;
		throw;
	}
	
	std::string str;
	while (getline(f, str)) {
		std::vector<std::string> vect = splitStringWithDelimiter(str, '/');
		if (vect.size() > 0) {
			if (vect[0] == "v") {
				Vector4f v(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0));
				arr.vertices.push_back(v);
			}
			else if (vect[0] == "vn") {
				Vector4f vn(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0), 0);
				arr.vertexNormal.push_back(vn);
			}
			else if (vect[0] == "vt") {
				Vector3f vt(strtof(vect[1].c_str(), 0), strtof(vect[2].c_str(), 0), strtof(vect[3].c_str(), 0));
				arr.vertexTexture.push_back(vt);
			}
			else if (vect[0] == "f") {
				std::vector<int> face;
				if (vect.size() == 10) { // has texture data
										 // index of vertices
					face.push_back(atoi(vect[1].c_str()) - 1); face.push_back(atoi(vect[4].c_str()) - 1); face.push_back(atoi(vect[7].c_str()) - 1);
					// index of normals
					face.push_back(atoi(vect[3].c_str()) - 1); face.push_back(atoi(vect[6].c_str()) - 1); face.push_back(atoi(vect[9].c_str()) - 1);
					// index of texture
					face.push_back(atoi(vect[2].c_str()) - 1); face.push_back(atoi(vect[5].c_str()) - 1); face.push_back(atoi(vect[8].c_str()) - 1);
				}
				else { // no texture data
					face.push_back(atoi(vect[1].c_str()) - 1); face.push_back(atoi(vect[3].c_str()) - 1); face.push_back(atoi(vect[5].c_str()) - 1);
					// index of normals
					face.push_back(atoi(vect[2].c_str()) - 1); face.push_back(atoi(vect[4].c_str()) - 1); face.push_back(atoi(vect[6].c_str()) - 1);
				}

				arr.faces.push_back(face);
			}
		}
	}
}

std::vector<std::string> splitStringWithDelimiter(std::string str, char c) {
	std::vector<std::string> vect;
	std::string substring;
	for (char & character : str) {
		if (character == c || character == ' ') {
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