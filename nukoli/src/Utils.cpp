#include "Utils.h"

std::random_device rd;
std::mt19937 gen(rd());

int GetRandInt(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
float GetRandFloat(int min, int max) {
	std::uniform_real_distribution<> dist(min, max);
	double x = dist(gen);
	return x;
}

BoundingBox::BoundingBox() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

BoundingBox::BoundingBox(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool isColliding(BoundingBox& b1, BoundingBox& b2) {
	int ax = b1.x;
	int ay = b1.y;
	int aw = b1.width;
	int ah = b1.height;
    int bx = b2.x;
    int by = b2.y;
    int bw = b2.width;
    int bh = b2.height;
    return ax < bx + bw &&
    ax + aw > bx &&
    ay < by + bh &&
    ay + ah > by;
}