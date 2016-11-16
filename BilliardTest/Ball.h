#pragma once
#include "DxLib.h"
#include "Math.h"
#include "Wall.h"

class CBall
{
public:
	CBall();
	CBall(int n, unsigned int c, float r);
	CBall(int n, unsigned int c, float r, VECTOR pos);
	~CBall();

	void Update();
	void Draw();
	void SetPosition(VECTOR);
	VECTOR GetPosition();
	VECTOR GetPower();
	void AddPower(VECTOR);
	void HitBall(CBall*,int);
	void HitWall(CWall * HitWall, int length);

private:
	int number;			//番号

	unsigned int color;

	float radius;		//半径
	float weight = 1.0f;		//重量

	VECTOR position;	//位置

	VECTOR power;		//力ベクトル
};

