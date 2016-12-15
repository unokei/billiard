#include "Predict.h"



CPredict::CPredict()
{
}


CPredict::~CPredict()
{
}

void CPredict::SetEndFlag(bool f) {
	EndFlag = f;
}

//�\�����̌v�Z�ƕ`��
void CPredict::HitPredict(CBall* balls, int BLength, CWall* walls,int WLength,CHole* holes,int HLength, VECTOR start,VECTOR power) {
	ray = VNorm(power);
	startPoint = start;

	radius = balls[0].GetRadius();
	
	CPredict* next = new CPredict;

	//�{�[���ɓ�����_���Z�o
	if (CalcHitPointforBall(balls, BLength) == false) {
		
		//�ǂɓ�����_���Z�o
		if (CalcHitPointforWall(walls, WLength) == true) {
			next->SetEndFlag(true);

			//�m�[�o�E���h�Ȃ玟�̐��𐶐�
			if (EndFlag == false) {
				next->HitPredict(balls, BLength, walls, WLength, holes,HLength,hitPoint, addPower);
			}
		}
		else {
			//���ɓ�����_���Z�o
			CalcHitPointforHole(holes, HLength);
		}
	}
	Draw();

	delete next;
}

//�{�[���ɓ�����_�C���������{�[���C���ˌ�̃x�N�g���̎Z�o
bool CPredict::CalcHitPointforBall(CBall* balls,int length) {
	float rad = radius * 2;
	float mindis = 1000;
	bool flag = false;

	for (int i = 1; i < length; i++) {
		VECTOR vectO = VSub(balls[i].GetPosition(), startPoint);

		float DotPowRay = VDot(vectO, ray);
		float DotPowPow = VDot(vectO, vectO);

		float s = DotPowRay * DotPowRay - DotPowPow + rad * rad;

		//���C���������Ă���Ȃ�
		if (s > 0) {
			float sq = sqrtf(s);
			float dist = DotPowRay - sq;

			//�O���ł��߂��ɂ�����̂�I��
			if (dist > 0 && dist < mindis) {
				hitPoint = VAdd(startPoint, VScale(ray, dist));
				hitBall = &balls[i];
				addPower = VSub(hitBall->GetPosition(), hitPoint);

				mindis = dist;
				flag = true;
			}
		}
	}
	return flag;
}

//�ǂɓ�����_�C���ˌ�̃x�N�g���̎Z�o
bool CPredict::CalcHitPointforWall(CWall* Walls, int length) {
	float mindis = 1000;
	bool flag = false;

	for (int i = 0; i < length; i++) {
		VECTOR v = VSub(Walls[i].GetStartPoint(), startPoint);
		VECTOR vWall = VSub(Walls[i].GetEndPoint(), Walls[i].GetStartPoint());

		float distWall = VCross(v, vWall).z / VCross(ray, vWall).z;
		float t = VCross(v, ray).z / VCross(ray, vWall).z;

		//�ł��߂��̂��̂�I��
		if (0 <= distWall && 0 <= t && t <= 1 && distWall < mindis) {
			hitPoint = VAdd(startPoint, VScale(ray, distWall - radius));
			addPower = VSub(ray, VScale(VScale(VScale(Walls[i].GetNormVector(), -1), VDot(ray, VScale(Walls[i].GetNormVector(), -1))), 2));

			mindis = distWall;
			flag = true;
		}

	}
	return flag;
}

//���ɓ�����_���Z�o
bool CPredict::CalcHitPointforHole(CHole* holes, int length){
	float rad = holes[0].GetRaidus();
	bool flag = false;

	for (int i = 0; i < length; i++) {
		VECTOR vectO = VSub(holes[i].GetCenter(), startPoint);

		float DotPowRay = VDot(vectO, ray);
		float DotPowPow = VDot(vectO, vectO);

		float s = DotPowRay * DotPowRay - DotPowPow + rad * rad;

		//���C���������Ă���Ȃ�
		if (s > 0) {
			float sq = sqrtf(s);
			float dist = DotPowRay - sq;

			//�O���̂��̂�I��
			if (dist > 0 ) {
				hitPoint = VAdd(startPoint, VScale(ray, dist));

				flag = true;
			}
		}
	}

	return flag;
}

//�`��
void CPredict::Draw() {

	//�\����
	DrawLine3D(startPoint, hitPoint,GetColor(255,255,255));

	//�~
	DrawCircleOnPlane(hitPoint, radius, 16, GetColor(255, 255, 255));
}


//�~�̕`��
void CPredict::DrawCircleOnPlane(VECTOR center, float radius, int divnum, unsigned int color) {

	VECTOR v = VGet(radius, 0.0f, 0.0f);
	MATRIX rotate = MGetRotZ(DX_PI_F * 2 / divnum);

	for (int i = 0; i < divnum; i++) {
		VECTOR nextv = VTransform(v, rotate);

		DrawLine3D(VAdd(center, v), VAdd(center, nextv), color);

		v = nextv;
	}
}
