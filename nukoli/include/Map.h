#pragma once
#include "Sprite.h"
#include "Rendering.h"

constexpr int mapSize = 1024;
class Map {
public:
	SpriteSheet* spriteSheet;
	std::vector<int> mapData = std::vector<int>(mapSize * mapSize, -1);
	void SetIndex(int x, int y, int index);
	int GetIndex(int x, int y);
	void Clear();
	Map();
	void loadFromFile(std::string fileName);



	
};


void DrawMap(Map& map,int x, int y, int mapX, int mapY, int width, int height, int scale=1);