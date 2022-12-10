#pragma once

#include <chrono>

class StopWatch {
	std::chrono::high_resolution_clock::time_point S;
	std::chrono::high_resolution_clock::time_point E;
public:

	typedef std::chrono::milliseconds TimeType;

	StopWatch() { Start(); };

	bool Start() {
		S = E = std::chrono::high_resolution_clock::now();
		return true;
	}
	bool ReStart() {
		return Start();
	}
	bool Stop() {
		E = std::chrono::high_resolution_clock::now();
		return true;
	}

	bool Reset() {
		S = E = std::chrono::high_resolution_clock::now();
		return true;
	}
	template<class T=TimeType>
	T Ellipse() {
		return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() -S);
	}
	template<class T=TimeType>
	T Result() {
		return std::chrono::duration_cast<T>(E - S);
	}
	
};