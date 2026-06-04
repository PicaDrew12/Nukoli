#include "Rendering.h"

void MoveCamera(int x, int y) {
	cameraX = x;
	cameraY = y;
}

void DrawPixel(int x, int y, uint8_t color)
{
	x -= cameraX;
	y-= cameraY;
	if (color == 16)
		return;

	if (x < 0 || x >= WIDTH ||
		y < 0 || y >= HEIGHT)
		return;

	frameBuffer[y * WIDTH + x] = color;
}

void DrawPixelAbsolute(int x, int y, uint8_t color)
{
	
	if (color == 16)
		return;

	if (x < 0 || x >= WIDTH ||
		y < 0 || y >= HEIGHT)
		return;

	frameBuffer[y * WIDTH + x] = color;
}






//void DrawPixel(int x, int y, uint8_t color) {
//	if (color != 16) {
//
//		int index = y * WIDTH + x;
//		frameBuffer[index] = color;
//		
//	}
//	
//}

void DrawSprite(Sprite& sprite, int x, int y, int scale, bool flipped) {
	for (int i = 0; i < sprite.height * scale /*&& y + i < HEIGHT*/; i++) {
		int spriteRow = i / scale;
		for (int j = 0; j < sprite.width * scale; j++) {
			int spriteCol = j / scale;
			if (flipped) spriteCol = sprite.width - 1 - spriteCol;
			uint8_t spriteColor = sprite.data[spriteRow * sprite.width + spriteCol];
			DrawPixel(x + j, y + i, spriteColor);
		}
	}
}


void DrawSprite(CompositeSprite& compositeSprite, int x, int y, int scale, bool flipped) {
	for (int i = 0; i < compositeSprite.tilesHigh; i++) {
		for (int j = 0; j < compositeSprite.tilesWide; j++) {
			Sprite currentSprite = compositeSprite.getTilebyCoord(j, i);
			int tileCol = j;
			if (flipped) tileCol = compositeSprite.tilesWide - 1 - tileCol;
			int newX = x + tileCol * 8*scale;
			int newY = y + i * 8*scale;

			DrawSprite(currentSprite, newX, newY,scale,flipped);
		}
	}
}
void DrawSprite2(AnimatedCompositeSprite& animatedCompositeSprite, int x, int y, int scale, bool flipped) {
	for (int i = 0; i < animatedCompositeSprite.tilesHigh; i++) {
		for (int j = 0; j < animatedCompositeSprite.tilesWide; j++) {
			Sprite currentSprite = animatedCompositeSprite.getTilebyCoord(j, i,animatedCompositeSprite.currentFrame);
			int tileCol = j;
			if (flipped) tileCol = animatedCompositeSprite.tilesWide - 1 - tileCol;
			int newX = x + tileCol * 8*scale;
			int newY = y + i * 8*scale;

			DrawSprite(currentSprite, newX, newY,scale,flipped);
		}
	}
}

void DrawSprite(AnimatedCompositeSprite& sprite, int posX, int posY, int scale, bool flipped)
{
    int frameSize = sprite.width * sprite.height;
    int start = frameSize * sprite.currentFrame;

    int tilesWide = sprite.tilesWide;

    for (int local = 0; local < frameSize; local++)
    {
        int idx = sprite.data[start + local];

        if (idx == 16)
            continue;

        int tileIndex = local / 64;
        int inTile = local % 64;

        int tileX = tileIndex % tilesWide;
        int tileY = tileIndex / tilesWide;

        int px = inTile % 8;
        int py = inTile / 8;

        int spriteX = tileX * 8 + px;
        int spriteY = tileY * 8 + py;

        if (flipped)
            spriteX = sprite.width - 1 - spriteX;

        int drawX = posX + spriteX * scale;
        int drawY = posY + spriteY * scale;

        DrawPixel(drawX, drawY, idx);
    }
}
void ClearFrameBuffer(uint8_t color) {
	for (int i = 0; i < SIZE; i++) {
		frameBuffer[i] = color;
	}
}


//PRIMITIVES

void DrawLine(int x1, int y1, int x2, int y2, uint8_t color, int thickness) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;
	bool steep = dy > dx;

	int lo = -(thickness - 1) >> 1;
	int hi = thickness >> 1;

	while (true) {
		for (int t = lo; t <= hi; t++) {
			int px = steep ? x1 + t : x1;
			int py = steep ? y1 : y1 + t;
			DrawPixel(px, py, color);
		}

		if (x1 == x2 && y1 == y2) break;

		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x1 += sx; }
		if (e2 < dx) { err += dx; y1 += sy; }
	}
}

void DrawRectangle(int x, int y, int width, int height, uint8_t color, bool fill, int thickness) {
	if (fill) {
		for (int i = y; i <y+ height; i++) {
			for (int j = x; j < x + width; j++) {
				DrawPixel(j, i, color);
			}
		}
	}
	else {
		for (int t = 0; t < thickness; t++) {
			
			for (int i = x; i < x + width; i++)
				DrawPixel(i, y + t, color);

			
			for (int i = x; i < x + width; i++)
				DrawPixel(i, y + height - 1 - t, color);

			
			for (int i = y; i < y + height; i++)
				DrawPixel(x + t, i, color);

			
			for (int i = y; i < y + height; i++)
				DrawPixel(x + width - 1 - t, i, color);
		}
	}
	
}

