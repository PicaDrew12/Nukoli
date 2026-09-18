#include "Nukoli.h"

SoundSource soundSource;
int angle =0;
bool flipH = false;
bool flipV = false;
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

    AnimatedCompositeSprite aba;
    void Start() override {
        initAudio();
        chick.loadFromFile("chick.cas");
        small.loadFromFile("f.sp");
        aba.loadFromFile("Abacrazy.cas");
        soundSource.loadFromFile("Fire_emblem_hot_talk.ns");
        soundSource.play();
        // RepeatForever(1,[&](){flip = !flip;Debug::Log(flip);});




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
        else if (isKeyPressed(Key::F)) {
            flipH = !flipH;
        }
        else if (isKeyPressed(Key::H)) {
            flipV = !flipV;
        }


    }

    void Draw() override {
    ClearFrameBuffer(7);
        // DrawSpriteRotate(angle,small,50,50,5,true,true);
        // DrawSpriteRotate(chick,100,100,7,flipH, flipV,angle);
        DrawSpriteRotate(aba,50,0,2,flipH,flipV,90);


    }
};


int main() {
    TestGame testGame;
    run(testGame);
    SaveDataFile();
}