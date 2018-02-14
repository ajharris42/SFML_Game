#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <memory>
#include <map>
#include <vector>

#include "rapidxml.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

struct Coordinate 
{
	int x, y;

	Coordinate(int paramx, int paramy) : x(paramx), y(paramy) {}
};

const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

const int TILE_SIZE = 32;

//Render Quads
#define DEBUG_RENDER false

#ifdef _DEBUG
	#define DEBUG_MODE true

	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>

	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#else
	#define DEBUG_MODE false
#endif