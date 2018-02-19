#pragma once
#include <string>
#include <vector>
#include "Triangle3DArray.h"
#include <iostream>
#include <fstream>
#include "Scene.h"

std::vector<std::string> splitString(std::string str);

std::vector<std::string> splitStringWithDelimiter(std::string str, char c);

std::vector<Triangle3D> readRawFile(const char * path);

std::vector<Triangle3D> readObjFile(const char * path);

Scene readSceneFile(const char * path);
