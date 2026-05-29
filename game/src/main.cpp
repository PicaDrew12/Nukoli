#include "Nukoli.h"
#include <cmath>
#include <cstdlib>

class TestGame : public Game {
    AnimatedCompositeSprite aba;
    void Start() override {
        aba.loadFromFile("Abacrazy.cas");
    }

    void Update() override {

    }

    void Draw() override {
        ClearFrameBuffer(3);
        DrawSprite(aba, 0, 0);
    }
};


void main() {
    TestGame testGame;
    testGame.gameName = "Nukoli";
    run(testGame);
}