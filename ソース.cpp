#include <iostream>
#include <chrono>
//#include <conio.h>

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
	template<class T = TimeType>
	T Ellipse() {
		return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - S);
	}
	template<class T = TimeType>
	T Result() {
		return std::chrono::duration_cast<T>(E - S);
	}
};
class DynamicCanceler {
public:
	bool operator()() {
		return F;
	}

	bool Update() {
		if (S.Ellipse<>() >= MS) {
			F = false;
			R = false;
			return false;
		}
		if (R) { S.ReStart(); }
		return F;
	}

	bool Raise(bool X) {
		if (X) { F = true; }
		R = X;
		return X;
	}

	bool SetInterval(std::chrono::milliseconds M) {
		MS = M;
		return true;
	}

protected:
	bool F = false;
	bool R = false;
	StopWatch S;
	std::chrono::milliseconds MS{ 1000 };
};
/** /
int KeyIn() {
	if (_kbhit()) {
		return _getch();
	}
	return -1;
}
/**/
template<class T>
class CountUpper {
public:
	CountUpper() {}
	CountUpper(const T& In) :X(In) {}
	const T& operator()() {
		return X;
	}
	bool Update() {
		X++;
		return true;
	}
protected:
	T X{};
};

int main() {
	DynamicCanceler D;
	CountUpper<int> C;
	D.Raise(true);

	while (D.Update())
	{
		C.Update();
		if (C()>=100) { D.Raise(false); }
		//if (KeyIn() != -1) { D.Raise(false); }
		std::cout << D() << std::endl;
	}

	return 0;
}