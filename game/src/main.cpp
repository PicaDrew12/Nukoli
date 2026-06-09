#include "Nukoli.h"
#include <cmath>
#include <cstdlib>

class Square {
public:

    int x;
    int y;
    int size;

    Square(int x, int y, int size) {
        this->x = x;
        this->y = y;
        this->size = size;
    }


};
void DrawSquare(Square& square, int color =9) {
    DrawRectangle(square.x, square.y, square.size, square.size, color);
}

void DrawBoundingBox(BoundingBox& box) {
    DrawRectangle(box.x, box.y, box.width, box.height, 7, false);
}

Square s1(0, 0, 50);
BoundingBox box(100, 100, 5, 5);
Square s2(100, 100, 50);
BoundingBox box2(100, 100, 5, 5);
class TestGame : public Game {


  
    void Start() override {
       

    }
    
    void Update() override {
        box.x = s1.x;
        box.y = s1.y;
        box.width = s1.size;
        box.height = s1.size;
        if (isKeyHeld(Key::W)) {
            s1.y -= 1;
        }
        if (isKeyHeld(Key::D)) {
            s1.x += 1;
        }
        if (isKeyHeld(Key::A)) {
            s1.x -= 1;
        }
        if (isKeyHeld(Key::S)) {
            s1.y += 1;
        }
        ////
        box2.x = s2.x;
        box2.y = s2.y;
        box2.width = s2.size;
        box2.height = s2.size;
        if (isKeyHeld(Key::Up)) {
            s2.y -= 1;
        }
        if (isKeyHeld(Key::Right)) {
            s2.x += 1;
        }
        if (isKeyHeld(Key::Left)) {
            s2.x -= 1;
        }
        if (isKeyHeld(Key::Down)) {
            s2.y += 1;
        }

       
       
    }

    void Draw() override {



        ClearFrameBuffer();
        DrawSquare(s1);
        DrawBoundingBox(box);
        DrawSquare(s2,4);
        DrawBoundingBox(box2);
        if (isColliding(box, box2)) {
            Print("Collision", 0, 10, 10, 1);
        }
       
        
        //std::cout << "j";
    }
};


int main() {
    TestGame testGame;
    testGame.gameName = "Nukoli";
    run(testGame);
}

