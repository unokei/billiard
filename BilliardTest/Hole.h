#pragma once
#include "DxLib.h"

class CHole
{
public:
	CHole();
	CHole(VECTOR, float);
	~CHole();
	VECTOR GetCenter();
	float GetRaidus();
	void Draw();

private:
	VECTOR center;	//ˆÊ’u
	float radius;
	void DrawCircleOnPlane(VECTOR center, float radius, int divnum, unsigned int color);
};

