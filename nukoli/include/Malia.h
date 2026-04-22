#pragma once
#include<functional>
#include<vector>
#include<memory>
#include<map>


class BaseTimer {
public:
	bool isExpired;
	float timestep;
	std::function<void()> callback;
	virtual void Update() = 0;
	void Stop();
};

extern std::vector<std::unique_ptr<BaseTimer>> timers;
extern std::unordered_map<int, BaseTimer*> timerMap;

class Timer: public BaseTimer {
public:
	float duration;
	Timer(float duration, std::function<void()> callback, float timestep = 1.0f / 60.0f);
	void Update() override;
	
	
};

class RepeatTimer :public BaseTimer {
public:
	float delay;
	float duration;
	int iterations;
	RepeatTimer(float delay, int iterations, std::function<void()> callback, float timestep = 1.0f / 60.0f);
	void Update() override;
	
};

class RepeatForeverTimer :public BaseTimer {
public:
	float delay;
	float duration;
	RepeatForeverTimer(float delay, std::function<void()> callback, float timestep = 1.0f / 60.0f);
	void Update() override;

};



void InitMalia();
void UpdateAllTimers();
int RunAfter(float seconds, std::function<void()> callback);
int RepeatFor(int iterations, float seconds, std::function<void()> callback);
int RepeatForever(float seconds, std::function<void()> callback);
BaseTimer* GetTimer(int index);

void CleanTimers();