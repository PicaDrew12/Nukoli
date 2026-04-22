#pragma once
#include "Sprite.h"
#include <unordered_map>
#include <cstdint>
#include <string>
#include <iostream>


//A font is always a 12 by 12 tiles cas
class Font {
public:
	uint8_t data[128][12][5];
	void loadFromFile(std::string filename);
	void testPrint(char c);



};

void PrintChar(char c,uint8_t color, int x, int y, int fontsize=1);
void Print(std::string text, uint8_t color, int x, int y, int fontSize=1, bool wrap=true,int maxLineLength=256);


