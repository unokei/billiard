#pragma once
#include "DxLib.h"
#include "Ball.h"
#include "Wall.h"
#include "Math.h"

class CPredict
{
public:
	CPredict();
	~CPredict();
	void SetEndFlag(bool f);
	void HitPredict(CBall* balls, int BLength, CWall* walls, int WLength, CHole* holes, int HLength, VECTOR start, VECTOR power);
	

private:
	VECTOR ray;
	VECTOR addPower;

	VECTOR startPoint;
	VECTOR hitPoint;
	CBall* hitBall;

	float radius;

	bool CalcHitPointforBall(CBall* balls, int length);
	bool CalcHitPointforWall(CWall* Walls, int length);
	bool CalcHitPointforHole(CHole* holes, int length);
	void Draw();
	void DrawCircleOnPlane(VECTOR center, float radius, int divnum, unsigned int color);

	int rayCount = 0;

	CPredict *next;

	bool EndFlag = false;

};

