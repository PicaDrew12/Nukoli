#pragma once
#include<random>



int GetRandInt(int min, int max);
float GetRandFloat(int min, int max);
class BoundingBox {
public:

	int x;
	int y;
	int width;
	int height;
	BoundingBox();
	BoundingBox(int x, int y, int width, int height);

};

bool isColliding(BoundingBox& b1, BoundingBox& b2);