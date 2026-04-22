#include "Sprite.h"
#include "Global.h"

void Sprite::loadFromFile(std::string filename) {
	std::ifstream fin(assetsFolder + filename);
	int color;
	int i = 0;
	while (fin >> color) {
		data[i] = color;
		i++;
	}
  
	
}


Sprite::Sprite() {
    uint8_t colors[64] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 11,
        11, 2, 11, 11, 11, 1, 1, 11, 2, 2,
        11, 2, 11, 1, 1, 11, 11, 2, 11, 11,
        2, 1, 1, 11, 2, 2, 11, 2, 11, 1,
        1, 11, 11, 2, 11, 2, 11, 1, 1, 2,
        2, 2, 2, 2, 2, 1, 1, 1, 1, 1,
        1, 1, 1, 1
    };

    
    for (int i = 0; i < 64; i++) {
        data[i] = colors[i];
    }
}


Sprite::Sprite(std::string path) {
    loadFromFile(path);
}


void SpriteSheet::loadFromFile(std::string filename) {
    std::ifstream fin(assetsFolder + filename);
    int color;
    int i = 0;
    while (fin >> color) {
        data.push_back(color);
        i++;
    }
    spriteCount= i/64;

}
Sprite SpriteSheet::getSpriteByIndex(int index) {
    Sprite tempSprite;
    int j = 0;
    for (int i = index * 64; i < index * 64 + 64; i++) {
        tempSprite.data[j] = data[i];
        j++;
    }
    return tempSprite;
}

Sprite CompositeSprite::getTileByIndex(int index) {
    Sprite tempSprite;
    int j = 0;
    for (int i = index * 64; i < index * 64 + 64; i++) {
        tempSprite.data[j] = data[i];
        j++;
    }
    return tempSprite;
}

Sprite CompositeSprite::getTilebyCoord(int x, int y) {
    int index = y * tilesWide + x;
    return getTileByIndex(index);
}

void CompositeSprite::loadFromFile(std::string filename) {
    std::ifstream fin(assetsFolder + filename);
    fin >> tilesWide;
    fin >> tilesHigh;
    int frames;
    fin >> frames;
    width = tilesWide * 8;
    height = tilesHigh * 8;
    tileCount = tilesWide * tilesHigh;
    int color;
    
    while (fin >> color) {
        data.push_back(color);
    }
}


void AnimatedCompositeSprite::loadFromFile(std::string filename, float frameDuration, bool looping) {
    std::ifstream fin(assetsFolder + filename);
    fin >> tilesWide;
    fin >> tilesHigh;
    fin >> frames;
    width = tilesWide * 8;
    height = tilesHigh * 8;
    currentFrame = 0;
    this->looping = looping;
    
    this->frameDuration = frameDuration;
    isRunning = true;
    tileCount = tilesHigh * tilesWide;
    timer->delay = frameDuration;
    int color;

    while (fin >> color) {
        data.push_back(color);
    }
}

CompositeSprite AnimatedCompositeSprite::getFrameByIndex(int index) {
    CompositeSprite tempComposite;
    tempComposite.width = width;
    tempComposite.height = height;
    tempComposite.tilesWide = tilesWide;
    tempComposite.tilesHigh = tilesHigh;
    tempComposite.tileCount = tileCount;
    int j = 0;
    for (int i = width * height * index; i < width * height * index + width * height; i++) {
        tempComposite.data.push_back(data[i]);
        j++;
    }
    return tempComposite;
}

Sprite AnimatedCompositeSprite::getTileByIndex(int index, int frame) {
    return getFrameByIndex(frame).getTileByIndex(index);
}

Sprite AnimatedCompositeSprite::getTilebyCoord(int x, int y, int frame) {
    return getFrameByIndex(frame).getTilebyCoord(x, y);
}

void AnimatedCompositeSprite::nextFrame() {
    if (isRunning) {
        if (looping) {
            currentFrame = (currentFrame + 1) % frames;
        }
        else {
            currentFrame++;
            if (currentFrame > frames-1) {
                currentFrame = frames - 1;
            }
        }
        
    }
    
}

void AnimatedCompositeSprite::pause() {
    isRunning = false;
}

void AnimatedCompositeSprite::play() {
    isRunning = true;
}

void AnimatedCompositeSprite::changeFrameDuration(float duration) {
    timer->delay = duration;
}

AnimatedCompositeSprite::~AnimatedCompositeSprite() {
    timers.erase(
        std::remove_if(timers.begin(), timers.end(),
            [this](const std::unique_ptr<BaseTimer>& ptr) {
                return ptr.get() == timer;
            }),
        timers.end() 
    );
    timer = nullptr;
}

AnimatedCompositeSprite::AnimatedCompositeSprite(const AnimatedCompositeSprite& other) : 
    width(other.width),
    height(other.height),
    tilesWide(other.tilesWide),
    tilesHigh(other.tilesHigh),
    frames(other.frames),
    currentFrame(other.currentFrame),
    data(other.data),
    tileCount(other.tileCount),
    frameDuration(other.frameDuration),
    isRunning(other.isRunning),
    looping(other.looping) {
    
    timer = static_cast<RepeatForeverTimer*>(timerMap[RepeatForever(frameDuration, [this]() { nextFrame(); })]);
    timer->delay = other.timer->delay;
    timer->duration = other.timer->duration;
    timer->isExpired = other.timer->isExpired;
    timer->timestep = other.timer->timestep;
    
}

AnimatedCompositeSprite& AnimatedCompositeSprite::operator=(const AnimatedCompositeSprite& other) {
    if (this == &other) return *this;

    width = other.width;
    height = other.height;
    tilesWide = other.tilesWide;
    tilesHigh = other.tilesHigh;
    frames = other.frames;
    currentFrame = other.currentFrame;
    data = other.data;
    tileCount = other.tileCount;
    frameDuration = other.frameDuration;
    isRunning = other.isRunning;
    looping = other.looping;

    timer->delay = other.timer->delay;
    timer->duration = other.timer->duration;
    timer->isExpired = other.timer->isExpired;
    timer->timestep = other.timer->timestep;

    return *this;
}



AnimatedCompositeSprite::AnimatedCompositeSprite(AnimatedCompositeSprite&& other) noexcept
    : width(other.width),
    height(other.height),
    tilesWide(other.tilesWide),
    tilesHigh(other.tilesHigh),
    frames(other.frames),
    currentFrame(other.currentFrame),
    data(std::move(other.data)),
    tileCount(other.tileCount),
    frameDuration(other.frameDuration),
    isRunning(other.isRunning),
    looping(other.looping)
{
    timer = static_cast<RepeatForeverTimer*>(timerMap[RepeatForever(frameDuration, [this]() { nextFrame(); })]);
    timer->delay = other.timer->delay;
    timer->duration = other.timer->duration;
    timer->isExpired = other.timer->isExpired;
    timer->timestep = other.timer->timestep;
    other.timer->Stop();
    other.isRunning = false;

}


//Object has valid timer no neeed to copy or create another, we just copy state
AnimatedCompositeSprite& AnimatedCompositeSprite::operator=(AnimatedCompositeSprite&& other) noexcept
{
    if (this != &other)
    {
        

        width = other.width;
        height = other.height;
        tilesWide = other.tilesWide;
        tilesHigh = other.tilesHigh;
        frames = other.frames;
        currentFrame = other.currentFrame;

        data = std::move(other.data);

        tileCount = other.tileCount;
        frameDuration = other.frameDuration;
        isRunning = other.isRunning;
        looping = other.looping;

       

        timer->delay = other.timer->delay;
        timer->duration = other.timer->duration;
        timer->isExpired = other.timer->isExpired;
        timer->timestep = other.timer->timestep;
        other.timer->Stop();
        other.isRunning = false;
    }

    return *this;
}



AnimatedCompositeSprite::AnimatedCompositeSprite()
    : width(0),
      height(0),
      tilesWide(0),
      tilesHigh(0),
      frames(1),
      currentFrame(0),
      tileCount(0),
      frameDuration(0.1f),
      isRunning(true),
      looping(true),
      timer(nullptr)
{
    timer = static_cast<RepeatForeverTimer*>(timerMap[RepeatForever(frameDuration, [&]() { nextFrame(); })]);
}