#pragma once
#include"Global.h"
#include"Sprite.h"


void DrawPixel(int x, int y, uint8_t color);
void DrawPixelAbsolute(int x, int y, uint8_t color);

void DrawSprite(Sprite& sprite,int x, int y, int scale=1, bool flipped = false);
void DrawSprite(CompositeSprite& compositeSprite, int x, int y, int scale = 1, bool flipped = false);
void DrawSprite(AnimatedCompositeSprite& animatedCompositeSprite, int x, int y, int scale = 1, bool flipped = false);

void ClearFrameBuffer(uint8_t color = t);

//PRIMITIVES

void DrawRectangle(int x, int y, int width, int height,uint8_t color ,bool fill = true, int thickness=1);
void DrawLine(int x1, int y1, int x2, int y2, uint8_t color, int thickness = 1);
//void DrawRectangle(int x, int y,int radius,uint8_t,  bool fill = true);
