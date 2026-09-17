#include "Nukoli.h"

SoundSource soundSource;
int angle =0;
bool flip = false;
void Pause() {
    angle = 0;
}

void Resume() {
    angle = 180;
}

class TestGame : public Game {
public:
    CompositeSprite chick;
    Sprite small;


    void Start() override {
        initAudio();
        chick.loadFromFile("chick.cas");
        small.loadFromFile("f.sp");
        soundSource.loadFromFile("Fire_emblem_hot_talk.ns");
        soundSource.play();
        RepeatForever(1,[&](){flip = !flip;Debug::Log(flip);});




    }

    void Update() override {
        if (isKeyPressed(Key::W)) {
            angle = 0;
        }else if (isKeyPressed(Key::D)) {
            angle = 90;
        }
        else if (isKeyPressed(Key::S)) {
            angle = 180;
        }
        else if (isKeyPressed(Key::A)) {
            angle = 270;
        }


    }

    void Draw() override {
    ClearFrameBuffer(2);
        DrawSpriteRotate(angle,small,50,50,5,flip);
        DrawSprite(chick,0,0,3,flip);


    }
};


int main() {
    TestGame testGame;
    run(testGame);
    SaveDataFile();
}