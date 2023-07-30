#pragma once
#include <unordered_map>
#include <thread>
#include <Windows.h>
#include <string>


class c_globals {
public:
	bool active = true;
	int tab = 0;
	int subTab = 0;		

};

class color_settings
{
public:
	float all[4] = { 0.20f, 0.20f, 0.20f, 255 };
};

inline c_globals globals;
inline color_settings color;

namespace mouse
{
	void Move(float x,float y, float x_multi);
	void click(int holdTime);

	inline bool active = true;
	inline int key = 0;
	inline float x;
	inline float y;
	inline float time;
}

namespace keyboard
{
	void pressKey(int key, int holdTime);
}

namespace thread // used for running features you add
{
	
}

