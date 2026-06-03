#pragma once
#include "Color.h"
#include<Malia.h>
#include <string>
class Font;

struct Config {
	bool useIntro;
	Config();
};





constexpr int WIDTH = 256;
constexpr int HEIGHT = 256;
constexpr int SIZE = WIDTH * HEIGHT;
extern uint8_t frameBuffer[WIDTH * HEIGHT];
extern Color palette[16];
extern Font defaultFont;
constexpr uint8_t t = 16;
extern const std::string assetsFolder;
extern Config gameConfig;
extern int cameraX;
extern int cameraY;
