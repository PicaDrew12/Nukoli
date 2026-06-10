#pragma once
#include <cstdint>
#include<string>
#include<fstream>
#include<vector>
#include<iostream>
#include "Malia.h"

class Sprite {
public:
	static constexpr int width = 8;
	static constexpr int height = 8;
	uint8_t data[width * height] = {};
	void loadFromFile(std::string filename);
	Sprite();
	Sprite(std::string path); 
};

class SpriteSheet {
public:
	std::vector<uint8_t> data;
	int spriteCount = 0;
	void loadFromFile(std::string filename);
	Sprite getSpriteByIndex(int index);
	


	

};

class CompositeSprite {
public:
	int width;
	int height;
	int tilesWide;
	int tilesHigh;
	std::vector<uint8_t> data;
	int tileCount;
	void loadFromFile(std::string filename);
	Sprite getTileByIndex(int index);
	Sprite getTilebyCoord(int x, int y);
};


class AnimatedCompositeSprite {
public:
	int width;
	int height;
	int tilesWide;
	int tilesHigh;
	int frames;
	int currentFrame;
	std::vector<uint8_t> data;
	int tileCount;
	float frameDuration; //in seconds
	bool isRunning;
	bool looping;
	RepeatForeverTimer* timer;
	void loadFromFile(std::string filename, float frameDuration =0.1f,bool looping =true);
	Sprite getTileByIndex(int index,int frame);
	Sprite getTilebyCoord(int x, int y,int frame);			
	CompositeSprite getFrameByIndex(int index);				
	void nextFrame();
	void pause();
	void play();
	void changeFrameDuration(float duration);
	AnimatedCompositeSprite();
	~AnimatedCompositeSprite();
	AnimatedCompositeSprite(const AnimatedCompositeSprite& other);  
	AnimatedCompositeSprite& operator=(const AnimatedCompositeSprite& other);
	AnimatedCompositeSprite(AnimatedCompositeSprite&& other) noexcept;
	AnimatedCompositeSprite& operator=(AnimatedCompositeSprite&& other) noexcept;
};

