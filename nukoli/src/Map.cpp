#include"Map.h"

//void Map::SetIndex(int x, int y, int index) {
//	mapData[x][y] = index;
//}
//
//int Map::GetIndex(int x, int y) {
//	return mapData[x][y];
//}


Map::Map() {

}




int getMapValue(const std::vector<int>& mapData,
	int x, int y)
{
	

	return mapData[y*mapSize+x];
}

void Map::SetIndex(int x, int y, int index) {
	
	mapData[y * mapSize + x] = index;
}

int Map::GetIndex(int x, int y) {
	
	return mapData[y * mapSize + x];
}

int getValue(const std::vector<int>& v, size_t index) {
	if (index < v.size()) {
		return v[index];
	}
	return -1;
}



void DrawMap(Map& map, int x, int y, int mapX, int mapY, int width, int height,int scale) {
	int ctw = 0;
	int cth = 0;
	for (int i = mapX; i < mapX + width; i++) {
		cth = 0;
		for (int j = mapY; j < mapY + height; j++) {
			int index;
			
			index = getMapValue(map.mapData,i,j);
			if (index != -1) {
				//DrawPixel(i, j, 8);

				Sprite sp = map.spriteSheet->getSpriteByIndex(index);
				DrawSprite(sp, x + ctw * 8*scale, y+cth * 8*scale,scale);

				
			}
			cth++;

		}
		ctw++;
	}
    
}


void Map::Clear() {
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			SetIndex(i, j, -1);
		}
	}
}

void Map::loadFromFile(std::string filename) {
	std::ifstream fin(assetsFolder + filename);

	int x;
	int y;
	int index;
	while (fin >> x >> y >> index) {
		SetIndex(x, y, index);
	}

}