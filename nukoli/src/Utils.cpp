#include Utils.h

std::random_device rd;
std::mt19937 gen(rd());

int GetRandInt(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
float GetRandFloat(int min, int max) {
	std::uniform_real_distribution<> dist(min, max);
	double x = dist(gen);
	return x;
}