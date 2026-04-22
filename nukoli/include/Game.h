#pragma once
#include<string>

class Game {
public:
	std::string gameName;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};