#pragma once
#include "DxLib.h"
#include "Math.h"

class CWall
{
public:
	CWall();
	CWall(VECTOR s, VECTOR e);
	~CWall();

	VECTOR GetNormVector();
	VECTOR GetStartPoint();
	VECTOR GetEndPoint();

	void Draw();



private:
	VECTOR startPoint;
	VECTOR endPoint;
	VECTOR heightVector;
	VECTOR normVector;
};

