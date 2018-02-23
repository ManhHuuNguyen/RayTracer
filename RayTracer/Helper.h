#pragma once
#include <string>
#include <vector>
#include "TriangleArray.h"
#include <iostream>
#include <fstream>
#include "Scene.h"
#include "Light.h"

std::vector<std::string> splitString(std::string str);

std::vector<std::string> splitStringWithDelimiter(std::string str, char c);

void readObjFile(const char * path, TriangleArray & arr);

Scene readSceneFile(const char * path);
