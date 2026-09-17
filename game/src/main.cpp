#include "Nukoli.h"

SoundSource soundSource;

void Pause() {
    soundSource.pause();
}

void Resume() {
    soundSource.resume();
}

class TestGame : public Game {
public:

    void Start() override {
        initAudio();

        soundSource.loadFromFile("Fire_emblem_hot_talk.ns");
        soundSource.play();




    }

    void Update() override {
        if (isKeyPressed(Key::Space)) {
            Pause();
        }else if (isKeyPressed(Key::R)) {
            Resume();
        }
    }

    void Draw() override {
    ClearFrameBuffer(0);


    }
};


int main() {
    TestGame testGame;
    run(testGame);
    SaveDataFile();
}