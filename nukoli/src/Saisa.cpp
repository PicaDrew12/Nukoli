#include "Saisa.h"
#include "Global.h"
#include "Rendering.h"

void Font::loadFromFile(std::string filename) {
	std::ifstream fin(assetsFolder+filename);
	if (!fin.is_open()) {
		std::cout << "Failed to open font file" << std::endl;
		return;
	}

	char c;
	for (int i = 0; i < 60; i++) {
		int val =0;
		data[' '][i / 5][i % 5] = val;
	}
	while (fin >> c) {
		for (int i = 0; i < 60; i++) {
			int val;
			fin >> val;
			data[c][i / 5][i % 5] = val;
		}
	}
}

void Font::testPrint(char c) {
	//std::cout << c;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {
			//std::cout << (int)data[c][i][j];
			std::cout << (data[c][i][j] ? '#' : ' ');
		}
		std::cout << std::endl;
	}
}

void PrintChar(char c, uint8_t color, int x, int y, int fontSize) {
	Font& font = defaultFont;
	for (int i = 0; i < 12*fontSize; i++) {
		for (int j = 0; j < 5*fontSize; j++) {
			int row = i / fontSize;
			int column = j / fontSize;
			uint8_t pixel = font.data[c][row][column];

			if (pixel != 0) {
				DrawPixel( x + j, y + i,color);
			}

		}
	}
}




void Print(std::string text, uint8_t color, int x, int y, int fontSize, bool wrap, int maxLineLength) {

	int textWidth = text.size() * 6 * fontSize;

	int i = 0;
	int length = x;
	

	for (char c : text) {

		
		if ((length + ((5 * fontSize + fontSize)) > maxLineLength || length + ((5 * fontSize + fontSize)) > 256)&&wrap) {
			y += 12*fontSize;
			i = 0;
			length = x;
		}
		PrintChar(c, color, x + i * (5 * fontSize + fontSize), y, fontSize);
		i++;
		length += 5 * fontSize + fontSize;
		
	}
}