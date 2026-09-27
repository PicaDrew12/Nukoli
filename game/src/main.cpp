#include "Nukoli.h"

SoundSource soundSource;
SoundSource soundSource2;
SoundSample sample(
      Note(1, 60, 0.5f),
      Note(2, 62, 0.25f),
      Note(4, 64, 1.0f)
  );
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
        sample.Play();
        chick.loadFromFile("chick.cas");
        small.loadFromFile("f.sp");
        aba.loadFromFile("Abacrazy.cas");
        soundSource.loadFromFile("Fire_emblem_hot_talk.ns");
        soundSource2.loadFromFile("use.ns");

        // soundSource.play();
        // soundSource2.play();
        // RunAfter(10,[&](){soundSource.pause();});
        // RepeatForever(1,[&](){flip = !flip;Debug::Log(flip);});
        // playNoise(128,defaultAmplitude,4);




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
    ClearFrameBuffer(6);
        DrawSprite(small,50,50,5,flipH,flipV,angle);
        DrawSprite(chick,100,100,7,flipH, flipV,angle);
        DrawSprite(aba,50,0,2,flipH,flipV,angle);


    }
};


int main() {
    TestGame testGame;
    run(testGame);
    SaveDataFile();
}