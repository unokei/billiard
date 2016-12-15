#pragma once
#include "DxLib.h"
#include "Math.h"
#include "Wall.h"
#include "Hole.h"

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
	float GetRadius();
	VECTOR GetPower();
	void AddPower(VECTOR);
	bool GetFallFlag();
	void FallRecover();
	void HitBall(CBall*,int);
	void HitWall(CWall * HitWall, int length);
	void FallinHole(CHole * hole, int length);

private:
	int number;			//�ԍ�

	unsigned int color;

	float radius;		//���a
	float weight = 1.0f;		//�d��

	VECTOR position;	//�ʒu

	VECTOR power;		//�̓x�N�g��

	bool fall = false;			//���������ǂ���
};

