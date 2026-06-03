#include "Nukoli.h"
#include <cmath>
#include <cstdlib>

float speed;

void SetSpeed() {
    speed = 1;
    if (noiseChannel.amplitude > 0) {
        speed += 1;
    }
    if (squareChannel1.amplitude > 0) {
        speed += 2;
    }
    if (squareChannel2.amplitude > 0) {
        speed += 2;
    }
    
    if (triangleChannel.amplitude > 0) {
        speed += 2;
    }
    if (sawToothChannel.amplitude > 0) {
        speed += 1;
    }

}

class TestGame : public Game {
    AnimatedCompositeSprite aba;
    CompositeSprite cos;
    SoundSource ss;
    int abaX = 0;
    int abaY = 0;
    void Start() override {
        cos.loadFromFile("eye.ncs");
        aba.loadFromFile("Abacrazy.cas");
        //aba.changeFrameDuration(1/speed);
        ss.loadFromFile("Fire_emblem_hot_talk.ns");
        RunAfter(5, [&]() {ss.reset();
            ss.loadFromFile("use.ns"); });
        RunAfter(10, [&]() {ss.reset();

            ss.loadFromFile("bigGirl.ns"); });
            
        initAudio();
        ss.play();

    }
    
    void Update() override {
        SetSpeed();
        // Handle directional input
        if (isKeyPressed(Key::W)) {
            cameraY -= 1;
            abaY -= 1;
            
        }
        if (isKeyPressed(Key::A)) {
            cameraX -= 1;
            abaX -= 1;
        }
        if (isKeyPressed(Key::S)) {
            cameraY += 1;
            abaY += 1;
        }
        if (isKeyPressed(Key::D)) {
            cameraX += 1;
            abaX += 1;
        }
        //aba.changeFrameDuration(1 / speed);
    }

    void Draw() override {



        ClearFrameBuffer(t);
        DrawSprite(cos,0,0);
        Print("Hello World", 3, 0, 0, 1,true,256,true);
        DrawSprite(aba, abaX, abaY);
        //std::cout << "j";
    }
};


void main() {
    TestGame testGame;
    testGame.gameName = "Nukoli";
    run(testGame);
}