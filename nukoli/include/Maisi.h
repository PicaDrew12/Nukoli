#pragma once
#include <SFML/Audio.hpp>
#include <cstdint>
#include <vector>
#include<cmath>
#include<random>
#include "Global.h"
#include<fstream>
#include "Malia.h"



extern float defaultAmplitude;



class SquareChannel : public sf::SoundStream {
public:
    std::atomic<float> frequency{ 440.0f };
    std::atomic<float> amplitude{ 4000.0f };
    std::atomic<float> duty{ 0.5f };

private:
    float phase = 0.0f;  
    static constexpr int BUFFER_SIZE = 1024;
    std::vector<std::int16_t> buffer;

    bool onGetData(Chunk& data) override {  
        buffer.resize(BUFFER_SIZE);
        float freq = frequency.load();
        float amp = amplitude.load();
        float d = duty.load();

        for (int i = 0; i < BUFFER_SIZE; ++i) {
            phase += freq / 44100.0f;
            if (phase >= 1.0f) phase -= 1.0f;
            float s = (phase < d) ? 1.0f : -1.0f;
            buffer[i] = static_cast<std::int16_t>(s * amp);
        }

        data.samples = buffer.data();
        data.sampleCount = BUFFER_SIZE;
        return true; // return false to stop
    }

    void onSeek(sf::Time) override {}

public:
    SquareChannel() {
        initialize(1, 44100, { sf::SoundChannel::Mono });
    }
};


class TriangleChannel : public sf::SoundStream {
public:
    std::atomic<float> frequency{ 440.0f };
    std::atomic<float> amplitude{ 4000.0f };
    std::atomic<float> duty{ 0.5f };

private:
    float phase = 0.0f;
    static constexpr int BUFFER_SIZE = 1024;
    std::vector<std::int16_t> buffer;

    bool onGetData(Chunk& data) override {
        buffer.resize(BUFFER_SIZE);
        float freq = frequency.load();
        float amp = amplitude.load();
        float d = duty.load();

        for (int i = 0; i < BUFFER_SIZE; ++i) {
            phase += freq / 44100.0f;
            if (phase >= 1.0f) phase -= 1.0f;
            float s = (phase < 0.5f) ? (4 * phase - 1) : (3 - 4 * phase);
            buffer[i] = static_cast<std::int16_t>(s * amp);
        }

        data.samples = buffer.data();
        data.sampleCount = BUFFER_SIZE;
        return true; // return false to stop
    }

    void onSeek(sf::Time) override {}

public:
    TriangleChannel() {
        initialize(1, 44100, { sf::SoundChannel::Mono });
    }
};


class SawToothChannel : public sf::SoundStream {
public:
    std::atomic<float> frequency{ 440.0f };
    std::atomic<float> amplitude{ 4000.0f };
    std::atomic<float> duty{ 0.5f };

private:
    float phase = 0.0f;
    static constexpr int BUFFER_SIZE = 1024;
    std::vector<std::int16_t> buffer;

    bool onGetData(Chunk& data) override {
        buffer.resize(BUFFER_SIZE);
        float freq = frequency.load();
        float amp = amplitude.load();
        float d = duty.load();

        for (int i = 0; i < BUFFER_SIZE; ++i) {
            phase += freq / 44100.0f;
            if (phase >= 1.0f) phase -= 1.0f;
            float s = 2.0f * phase - 1;
            buffer[i] = static_cast<std::int16_t>(s * amp);
        }

        data.samples = buffer.data();
        data.sampleCount = BUFFER_SIZE;
        return true; // return false to stop
    }

    void onSeek(sf::Time) override {}

public:
    SawToothChannel() {
        initialize(1, 44100, { sf::SoundChannel::Mono });
    }
};

float decayRate(int midiNote);

class NoiseChannel : public sf::SoundStream {
public:
    std::atomic<int>   midiNote{ 0 };
    std::atomic<float> amplitude{ 4000.0f };
    std::atomic<bool>  triggered{ false }; // set true when a new note starts

private:
    static constexpr int BUFFER_SIZE = 1024;
    std::vector<std::int16_t> buffer;
    std::mt19937 rng{ std::random_device{}() };  // seeded once at construction
    std::uniform_real_distribution<float> dist{ -1.0f, 1.0f };
    float t = 0.0f; // time within current note, in samples / sampleRate

    bool onGetData(Chunk& data) override {
        buffer.resize(BUFFER_SIZE);
        float amp = amplitude.load();
        float decay = decayRate(midiNote.load());

        if (triggered.exchange(false))
            t = 0.0f; // reset envelope on new note

        for (int i = 0; i < BUFFER_SIZE; ++i) {
            float envelope = std::exp(-t * decay);
            float s = dist(rng) * envelope;
            buffer[i] = static_cast<std::int16_t>(s * amp);
            t += 1.0f / 44100.0f;
        }

        data.samples = buffer.data();
        data.sampleCount = BUFFER_SIZE;
        return true;
    }

    void onSeek(sf::Time) override {}

public:
    NoiseChannel() {
        initialize(1, 44100, { sf::SoundChannel::Mono });
    }
};
extern SquareChannel squareChannel1;
extern SquareChannel squareChannel2;
extern TriangleChannel triangleChannel;
extern SawToothChannel sawToothChannel;
extern NoiseChannel noiseChannel;

struct Note {
    int channel;
    uint8_t noteNumber;
    float duration;
    float delay;

};

//class SoundSource {
//public:
//    std::vector<Note> squareChannel1Notes;
//    std::vector<Note> squareChannel2Notes;
//    std::vector<Note> triangleChannelNotes;
//    std::vector<Note> sawToothChannelNotes;
//    std::vector<Note> noiseChannelNotes;
//
//    //
//    int square1NoteIndex;
//    int square2NoteIndex;
//    int triangleNoteIndex;
//    int sawToothNoteIndex;
//    int noiseNoteIndex;
//
//    void square2NextNote();
//    void loadFromFile(std::string filename);
//    void play();
//};

extern const int sampleRate;
//extern const int duration;
//extern const int count;
//extern std::vector<int16_t> samples;


void initAudio();
void playSamples(std::vector<int16_t>& samples, size_t count, sf::SoundBuffer& buffer, sf::Sound& channel);
void playSquare(float frequency, float amplitude, float duration, int buffer);
void playTriangle(float frequency, float amplitude, float duration);
void playSawTooth(float frequency, float amplitude, float duration);
void playNoise(int midiNote, float amplitude, float duration);
void playNote(Note& note);

class SoundSource {
public:
    std::vector<Note> squareChannel1Notes;
    std::vector<Note> squareChannel2Notes;
    std::vector<Note> triangleChannelNotes;
    std::vector<Note> sawToothChannelNotes;
    std::vector<Note> noiseChannelNotes;

    //
    int square1NoteIndex;
    int square2NoteIndex;
    int triangleNoteIndex;
    int sawToothNoteIndex;
    int noiseNoteIndex;

    void square1NextNote();
    void square2NextNote();
    void triangleNextNote();
    void sawToothNextNote();
    void noiseNextNote();
    void loadFromFile(std::string filename);
    void play();
    void stop();
    void reset();
};
