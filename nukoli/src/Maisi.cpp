#include "Maisi.h"
#include <cmath>
#include<iostream>
#include <cstdint>


const int sampleRate = 44100;
float defaultAmplitude = 4000;
SquareChannel squareChannel1;
SquareChannel squareChannel2;
TriangleChannel triangleChannel;
SawToothChannel sawToothChannel;
NoiseChannel noiseChannel;


void playSquare(float frequency, float amplitude, float  duration, int buffer) {
	if (buffer == 1) {
		squareChannel1.amplitude = amplitude;
		squareChannel1.frequency = frequency;
		RunAfter(duration, []() {squareChannel1.amplitude = 0; });
	}
	if (buffer == 2) {
		squareChannel2.amplitude = amplitude;
		squareChannel2.frequency = frequency;
		RunAfter(duration, []() {squareChannel2.amplitude = 0; });
	}

}

void playTriangle(float frequency, float amplitude, float duration) {
	triangleChannel.amplitude = amplitude/0.577f;
	triangleChannel.frequency = frequency;
	RunAfter(duration, []() {triangleChannel.amplitude = 0; });

}


void playSawTooth(float frequency, float amplitude, float duration) {
	sawToothChannel.amplitude = amplitude/0.577f;
	sawToothChannel.frequency = frequency;
	RunAfter(duration, []() {sawToothChannel.amplitude = 0; });

}


//void playTriangle(float)

float decayRate(int midiNote) {
	switch (midiNote) {
		// bass drums — punchy, very short
	case 35: case 36:
		return 12.0f;

		// snares, clap, side stick — sharp attack, medium decay
	case 37: case 38: case 39: case 40:
		return 8.0f;

		// toms — medium, slightly longer than snare
	case 41: case 43: case 45: case 47:
	case 48: case 50:
		return 6.0f;

		// closed and pedal hi-hat — very tight
	case 42: case 44:
		return 20.0f;

		// open hi-hat — washy, longer
	case 46:
		return 4.0f;

		// crash cymbals, splash, chinese — long wash
	case 49: case 52: case 55: case 57:
		return 1.5f;

		// ride cymbals, ride bell — long but tighter than crash
	case 51: case 53: case 59:
		return 2.5f;

		// cowbell, wood blocks, claves — short, percussive click
	case 56: case 75: case 76: case 77:
		return 15.0f;

		// tambourine, maracas, cabasa — short shaker sounds
	case 54: case 69: case 70:
		return 10.0f;

		// bongos, congas, timbales — mid decay
	case 60: case 61: case 62: case 63:
	case 64: case 65: case 66:
		return 7.0f;

		// triangles — medium-long ring
	case 80: case 81:
		return 3.0f;

		// whistles, guiro, vibraslap, cuica — variable, use medium
	default:
		return 8.0f;
	}
}

void playNoise(int midiNote, float amplitude, float duration) {
	if (midiNote > 128) {
		return;
	}
	noiseChannel.amplitude = amplitude;
	noiseChannel.midiNote = midiNote;   
	noiseChannel.triggered = true;
	RunAfter(duration, []() {noiseChannel.amplitude = 0; });

	//playSamples(samples, count, noiseChannel);
}
   
float midiToFreq(int note) {
	return 440.0f * exp2f((note - 69) / 12.0f);
}


void playNote(Note& note) {
	float frequency = midiToFreq(note.noteNumber);
	if (note.channel == 0) {
		playSquare(frequency, defaultAmplitude, note.duration, 1);
	}
	else if (note.channel == 1) {
		playSquare(frequency, defaultAmplitude, note.duration, 2);

	}
	else if (note.channel == 2) {
		playTriangle(frequency, defaultAmplitude, note.duration);
	}
	else if (note.channel == 3) {
		playSawTooth(frequency, defaultAmplitude, note.duration);
	}
	else if (note.channel == 4) {
		playNoise(note.noteNumber, defaultAmplitude, note.duration);
	}
}





void SoundSource::loadFromFile(std::string filename) {
	std::ifstream fin(assetsFolder+ "/sounds/" + filename);
	int channelIndex = 0;
	int value;
	while (fin >> value) {
		if (value == -1) {
			channelIndex++;
			continue;
		}
		else {
			Note note;

			//fin >> note.noteNumber;
			note.noteNumber = value;
			note.channel = channelIndex;
			fin >> note.duration;
			fin >> note.delay;
			if (note.channel == 0) {
				squareChannel1Notes.push_back(note);

			}
			else if (note.channel == 1) {
				squareChannel2Notes.push_back(note);

			}
			else if (note.channel == 2) {
				triangleChannelNotes.push_back(note);
			}
			else if (note.channel == 3) {
				sawToothChannelNotes.push_back(note);
			}
			else if (note.channel == 4) {
				noiseChannelNotes.push_back(note);
			}
		}


	}

}

void SoundSource::square1NextNote() {
	if (square1NoteIndex < squareChannel1Notes.size()) {
		Note noteToPlay = squareChannel1Notes[square1NoteIndex];
		playNote(noteToPlay);
		square1NoteIndex++;
		RunAfter(noteToPlay.duration + noteToPlay.delay, [this]() { square1NextNote(); });
	}
	else {
		std::cout << "SQUARE 1 DONE" << std::endl;
	}
}

void SoundSource::square2NextNote() {
	if (square2NoteIndex < squareChannel2Notes.size()) {
		Note noteToPlay = squareChannel2Notes[square2NoteIndex];
		playNote(noteToPlay);
		square2NoteIndex++;
		RunAfter(noteToPlay.duration + noteToPlay.delay, [this]() { square2NextNote(); });
	}
	else {
		std::cout << "SQUARE 2 DONE" << std::endl;
	}
}


void SoundSource::triangleNextNote() {
	if (triangleNoteIndex < triangleChannelNotes.size()) {
		Note noteToPlay = triangleChannelNotes[triangleNoteIndex];
		playNote(noteToPlay);
		triangleNoteIndex++;
		RunAfter(noteToPlay.duration + noteToPlay.delay, [this]() { triangleNextNote(); });
	}
	else {
		std::cout << "TRIANGLE DONE" << std::endl;
	}
}

void SoundSource::sawToothNextNote() {
	if (sawToothNoteIndex < sawToothChannelNotes.size()) {
		Note noteToPlay = sawToothChannelNotes[sawToothNoteIndex];
		playNote(noteToPlay);
		sawToothNoteIndex++;
		RunAfter(noteToPlay.duration + noteToPlay.delay, [this]() { sawToothNextNote(); });
	}
	else {
		std::cout << "SAWTOOTH DONE" << std::endl;
	}
}

void SoundSource::noiseNextNote() {
	if (noiseNoteIndex < noiseChannelNotes.size()) {
		Note noteToPlay = noiseChannelNotes[noiseNoteIndex];
		playNote(noteToPlay);
		noiseNoteIndex++;
		RunAfter(noteToPlay.duration + noteToPlay.delay, [this]() { noiseNextNote(); });
	}
	else {
		std::cout << "NOISE DONE" << std::endl;
	}
}


void SoundSource::play() {
	square1NoteIndex = 0;
	square2NoteIndex = 0;
	triangleNoteIndex = 0;
	sawToothNoteIndex = 0;
	noiseNoteIndex = 0;
	square1NextNote();
	square2NextNote();
	triangleNextNote();
	sawToothNextNote();
	noiseNextNote();
}



void initAudio() {
	squareChannel1.amplitude = 0;
	squareChannel1.play();
	squareChannel2.amplitude = 0;
	squareChannel2.play();
	triangleChannel.amplitude = 0;
	triangleChannel.play();
	sawToothChannel.amplitude = 0;
	sawToothChannel.play();
	noiseChannel.amplitude = 0;
	noiseChannel.play();

}


void SoundSource::reset() {
	squareChannel1Notes.clear();
	squareChannel2Notes.clear();
	triangleChannelNotes.clear();
	sawToothChannelNotes.clear();
	noiseChannelNotes.clear();
	square1NoteIndex = 0;
	square2NoteIndex = 0;
	triangleNoteIndex = 0;
	sawToothNoteIndex = 0;
	noiseNoteIndex = 0;

	squareChannel1.amplitude = 0;
	squareChannel2.amplitude = 0;
	triangleChannel.amplitude = 0;
	sawToothChannel.amplitude = 0;
	noiseChannel.amplitude = 0;
}