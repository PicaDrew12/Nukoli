#include "Malia.h"
#include<iostream>


std::vector<std::unique_ptr<BaseTimer>> timers;
std::unordered_map<int, BaseTimer*> timerMap;
int timerIndex = 0;

void BaseTimer::Stop() {
	isExpired = true;
}

Timer::Timer(float duration, std::function<void()> callback, float timestep) {
	this->duration = duration;
	this->timestep = timestep;
	this->callback = callback;
	isExpired = false;
}

RepeatTimer::RepeatTimer(float delay, int iterations, std::function<void()> callback, float timestep) {
	this->delay = delay;
	this->iterations = iterations;
	this->callback = callback;
	duration = delay;
	isExpired = false;
	this->timestep = timestep;
}
RepeatForeverTimer::RepeatForeverTimer(float delay, std::function<void()> callback, float timestep) {
	this->delay = delay;
	this->callback = callback;
	duration = delay;
	isExpired = false;
	this->timestep = timestep;
}

void CleanTimers() {
	auto newEnd = std::remove_if(timers.begin(), timers.end(), [](const auto& element) {
		return element->isExpired;
		});
	timers.erase(newEnd, timers.end());
}

void Timer::Update() {
	if (!isExpired) {
		duration -= timestep;
		if (duration <= 0) {
			if(callback)
				callback();
			isExpired = true;
		}
	}
}

void RepeatTimer::Update() {

	if (!isExpired) {

		duration -= timestep;
		//std::cout << duration<<std::endl;
		if (iterations > 0) {
			if (duration <= 0) {
				if (callback)
					callback();
				duration = delay;
				iterations--;
			}
		}
		else {
			isExpired = true;
		}
	}
}
	

void RepeatForeverTimer::Update() {
	if (!isExpired) {

		duration -= timestep;
		//std::cout << duration<<std::endl;
		
			if (duration <= 0) {
				if (callback)
					callback();
				duration = delay;
				
			}
		
	}
}


void InitMalia() {

}

//void UpdateAllTimers() {
//	for (auto& timerPointer : timers) {
//		//std::cout << timers.size();
//		timerPointer->Update();
//	}
//	CleanTimers();
//}

void UpdateAllTimers() {
	// Create a copy of raw pointers to avoid iterator invalidation
	std::vector<BaseTimer*> timersCopy;
	timersCopy.reserve(timers.size());
	for (const auto& timer : timers) {
		timersCopy.push_back(timer.get());
	}

	// Update timers from the copy
	for (auto timer : timersCopy) {
		// Check if timer still exists (it may have been removed during callbacks)
		if (!timer->isExpired) {
			timer->Update();
		}
	}
	CleanTimers();
}


int RunAfter(float seconds, std::function<void()> callback) {
	auto newTimer = std::make_unique<Timer>(seconds, callback);
	timers.push_back(std::move(newTimer));
	int index = timerIndex;
	timerIndex++;
	timerMap[index] = timers[timers.size() - 1].get();
	return index;
}

	
int RepeatFor(int iterations, float seconds, std::function<void()> callback) {
	auto newTimer = std::make_unique<RepeatTimer>(seconds,iterations,callback);

	timers.push_back(std::move(newTimer));
	int index = timerIndex;
	timerIndex++;
	timerMap[index] = timers[timers.size() - 1].get();
	return index;
}

int RepeatForever(float seconds, std::function<void()> callback) {
	auto newTimer = std::make_unique<RepeatForeverTimer>(seconds, callback);

	timers.push_back(std::move(newTimer));
	int index = timerIndex;
	timerMap[index] = timers[timers.size() - 1].get();
	timerIndex++;
	
	return index;
}


BaseTimer* GetTimer(int index) {
	return timerMap[index];
}