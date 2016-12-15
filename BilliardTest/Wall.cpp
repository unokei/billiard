#include "Wall.h"



CWall::CWall()
{
	startPoint = VGet(0.0f, 0.0f, 0.0f);
	endPoint = VGet(1.0f, 0.0f, 0.0f);
	heightVector = VGet(0.0f, 0.0f, 1.0f);
	normVector = VNorm(VCross(VSub(endPoint, startPoint), heightVector));
}

CWall::CWall(VECTOR s,VECTOR e)
{
	startPoint = s;
	endPoint = e;
	heightVector = VGet(0.0f, 0.0f, 1.0f);
	normVector = VNorm(VCross(VSub(endPoint, startPoint), heightVector));
}


CWall::~CWall()
{
}

VECTOR CWall::GetNormVector() {
	return normVector;
}

VECTOR CWall::GetStartPoint() {
	return startPoint;
}

VECTOR CWall::GetEndPoint() {
	return endPoint;
}

void CWall::Draw() {
	DrawLine3D(startPoint, endPoint, GetColor(255, 255, 255));
	DrawLine3D(VSub(startPoint,VScale(heightVector,5.0f)), VSub(endPoint,VScale(heightVector, 5.0f)), GetColor(255, 255, 255));
	DrawLine3D(startPoint, VSub(startPoint, VScale(heightVector, 5.0f)), GetColor(255, 255, 255));
	DrawLine3D(endPoint, VSub(endPoint, VScale(heightVector, 5.0f)), GetColor(255, 255, 255));
}