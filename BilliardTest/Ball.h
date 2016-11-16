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
	int number;			//�ԍ�

	unsigned int color;

	float radius;		//���a
	float weight = 1.0f;		//�d��

	VECTOR position;	//�ʒu

	VECTOR power;		//�̓x�N�g��
};

