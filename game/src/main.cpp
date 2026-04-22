#include "Nukoli.h"



SoundSource music;
std::string playing;

void changeSong() {
	music.reset();
	std::string fileName;

	std::cout << "FILENAME: ";
	std::cin >> fileName;
	
	playing = fileName;
	music.loadFromFile(fileName+".ns");
}



class TestGame :public Game {
	


	CompositeSprite jake;
	void Start() override {
		initAudio();
		std::string fileName;
		std::cin >> fileName;
		playing = fileName;
		jake.loadFromFile("jake.cas");
		music.loadFromFile(fileName + ".ns");
		music.play();


	};
	void Update() override {
		if (isKeyPressed(Key::Space)) {
			changeSong();
		}
	
	};
	void Draw() override {
		ClearFrameBuffer(5);
		DrawSprite(jake, 0, 0);
		Print("Now playing: " + playing, 11, 0, 256-12*4, 2);
	};
};

void main() {
	TestGame testGame;
	testGame.gameName = "ChiptunePlayer";
	run(testGame);  
}