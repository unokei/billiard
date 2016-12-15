#include "DxLib.h"
#include "Ball.h"
#include "Wall.h"
#include "Hole.h"
#include "Predict.h"

#define BALL_NUM 10
#define BALL_RAD 5.7f / 2.0f
#define WALL_NUM 24
#define HOLE_NUM 6
#define ROOT3 1.73205080757f

CPredict Predicter;

//�i�C���{�[���̏����z�u
void NineBallInit(CBall* balls) {

	float x = 0;
	float y = 55.0f;
	float z = 0;

	float placerad = BALL_RAD + 0.1f;
	float tatehaba = ROOT3 * placerad;

	//���
	balls[0] = CBall(0, GetColor(220, 220, 200)	, BALL_RAD, VGet(x					, y - 120.0f		, z));

	//�I��
	balls[1] = CBall(1, GetColor(255, 255, 0)	, BALL_RAD, VGet(x					, y - tatehaba * 2	, z));
	balls[2] = CBall(2, GetColor(0, 0, 255)		, BALL_RAD, VGet(x + placerad		, y - tatehaba		, z));
	balls[3] = CBall(3, GetColor(255, 0, 0)		, BALL_RAD, VGet(x - placerad		, y - tatehaba		, z));
	balls[4] = CBall(4, GetColor(255, 0, 255)	, BALL_RAD, VGet(x + placerad * 2	, y					, z));
	balls[5] = CBall(5, GetColor(255, 128, 0)	, BALL_RAD, VGet(x - placerad * 2	, y					, z));
	balls[6] = CBall(6, GetColor(0, 255, 0)		, BALL_RAD, VGet(x + placerad		, y + tatehaba		, z));
	balls[7] = CBall(7, GetColor(255, 0, 128)	, BALL_RAD, VGet(x - placerad		, y + tatehaba		, z));
	balls[8] = CBall(8, GetColor(128, 0, 255)	, BALL_RAD, VGet(x					, y + tatehaba * 2	, z));
	balls[9] = CBall(9, GetColor(255, 200, 50)	, BALL_RAD, VGet(x					, y					, z));

}

//�ǂ̔z�u
void WallInit(CWall* walls) {
	float narrowSide = 125.0f;
	float longSide = 220.0f;
	
	float inter = 7.5f;
	float gate = inter * 0.7f;

	float topO = longSide / 2.0f;
	float topI = topO - inter;

	float sideO = narrowSide / 2.0f;
	float sideI = sideO - inter;

	VECTOR basePoint = VGet(narrowSide * (-0.5f), longSide * ( - 0.5f), 0.0f);

	walls[0] = CWall(VGet(-sideI,topO,0), VGet(-(sideI - inter), topI, 0));
	walls[1] = CWall(VGet(-(sideI - inter), topI, 0), VGet((sideI - inter), topI, 0));
	walls[2] = CWall(VGet((sideI - inter), topI, 0), VGet(sideI, topO, 0));
	walls[18] = CWall(VGet(sideI, topO, 0), VGet(-sideI, topO, 0));

	walls[3] = CWall(VGet(sideO, topI, 0), VGet(sideI, (topI - inter), 0));
	walls[4] = CWall(VGet(sideI, (topI - inter), 0), VGet(sideI, gate, 0));
	walls[5] = CWall(VGet(sideI, gate, 0), VGet(sideO, gate, 0));
	walls[19] = CWall(VGet(sideO, gate, 0), VGet(sideO, topI, 0));

	walls[6] = CWall(VGet(sideO, -gate, 0), VGet(sideI, -gate, 0));
	walls[7] = CWall(VGet(sideI, -gate, 0), VGet(sideI, -(topI - inter), 0));
	walls[8] = CWall(VGet(sideI, -(topI - inter), 0), VGet(sideO, -topI, 0));
	walls[20] = CWall(VGet(sideO, -topI, 0), VGet(sideO, -gate, 0));

	walls[9] = CWall(VGet(sideI, -topO, 0), VGet((sideI - inter), -topI, 0));
	walls[10] = CWall(VGet((sideI - inter), -topI, 0), VGet(-(sideI - inter), -topI, 0));
	walls[11] = CWall(VGet(-(sideI - inter), -topI, 0), VGet(-sideI, -topO, 0));
	walls[21] = CWall(VGet(-sideI, -topO, 0), VGet(sideI, -topO, 0));

	walls[12] = CWall(VGet(-sideO, -topI, 0), VGet(-sideI, -(topI - inter), 0));
	walls[13] = CWall(VGet(-sideI, -(topI - inter), 0), VGet(-sideI, -gate, 0));
	walls[14] = CWall(VGet(-sideI, -gate, 0), VGet(-sideO, -gate, 0));
	walls[22] = CWall(VGet(-sideO, -gate, 0), VGet(-sideO, -topI, 0));

	walls[15] = CWall(VGet(-sideO, gate, 0), VGet(-sideI, gate, 0));
	walls[16] = CWall(VGet(-sideI, gate, 0), VGet(-sideI, topI - inter, 0));
	walls[17] = CWall(VGet(-sideI, topI - inter, 0), VGet(-sideO, topI, 0));
	walls[23] = CWall(VGet(-sideO, topI, 0), VGet(-sideO, gate, 0));
}

//���̔z�u
void HoleInit(CHole* holes) {
	float xInterval = 125.0f / 2.0;
	float yInterval = 220.0f / 2.0f;

	float rad = 7.5f;
	float gate = rad * 0.7f;

	holes[0] = CHole(VGet(-xInterval, -yInterval, 0.0f), rad);
	holes[1] = CHole(VGet(-(xInterval + gate), 0, 0.0f), rad);
	holes[2] = CHole(VGet(-xInterval, yInterval, 0.0f), rad);
	holes[3] = CHole(VGet( xInterval, -yInterval, 0.0f), rad);
	holes[4] = CHole(VGet( xInterval + gate, 0, 0.0f), rad);
	holes[5] = CHole(VGet( xInterval, yInterval, 0.0f), rad);
}

//�`��C�J�����C���C�g�Ȃǂ̐ݒ�
void GlaphicsInit() {
	SetDrawScreen(DX_SCREEN_BACK);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	//SetDrawMode(DX_DRAWMODE_BILINEAR);

	//�J�����̈ʒu�p�x�ݒ�
	SetCameraPositionAndTargetAndUpVec(VGet(70.0f, 0.0f, -165.0f), VGet(12.5f, 0.0f, 0.0f), VGet(-1.0f, 0.0f, 0.0f));

	//�J�����ݒ�
	SetupCamera_Perspective(1.0472f);

	ChangeLightTypePoint(VGet(0.0f, 0.0f, -2000.0f), 2500.0f, 0.0f, 0.0006f, 0.0f);
	SetGlobalAmbientLight(GetColorF(1.0f, 0.9f, 0.5f, 0.0f));

}

//��Ԓ��̃}�E�X���W�̎擾
VECTOR GetMousePos() {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	VECTOR startP = ConvScreenPosToWorldPos(VGet((float)mouseX, (float)mouseY, 0.0f));	//�}�E�X�̃��[���h���W�i���s0�j
	VECTOR endP = ConvScreenPosToWorldPos(VGet((float)mouseX, (float)mouseY, 1.0f));		//�}�E�X�̃��[���h���W�i���s�ő�j
	VECTOR ray = VNorm(VSub(endP, startP));	//�}�E�X�ւ̃��C

	float scale = (0.0f - startP.z) / ray.z;
	VECTOR worldP = VAdd(startP, VScale(ray, scale));	//���C��z��0.0�̍��W���Z�o

	return worldP;
}

//�S�{�[���̒�~���`�F�b�N
bool CheckBallStop(CBall *balls) {
	for (int i = 0; i < BALL_NUM; i++) {
		if (VSize(balls[i].GetPower()) != 0.0f) {
			return false;
		}
	}
	return true;
}

//�V���b�g�x�N�g���̎Z�o
VECTOR CalcShotVector(CBall * cueball) {
	VECTOR worldP = GetMousePos();

	float shotmax = 50.0f;

	float cuedist = VSize(VSub(worldP, cueball->GetPosition()));
	if (cuedist > shotmax) cuedist = shotmax;

	VECTOR shotVector = VScale(VNorm(VSub(cueball->GetPosition(), worldP)), cuedist);

	return shotVector;
}

//�L���[�̕`��
void DrawCue(VECTOR ballpos,VECTOR shotvect) {
	float cuelong = 100.0f;

	VECTOR cueVector = VScale(shotvect,-1);

	VECTOR cueStartPos = VAdd(ballpos, cueVector);
	VECTOR cueEndPos = VAdd(cueStartPos,VScale(VNorm(cueVector),cuelong));

	//�`��@�Ƃ肠�����J�v�Z���ő�p
	DrawCapsule3D(cueStartPos, cueEndPos, 1.0f, 8, GetColor(70, 20, 0), GetColor(255, 255, 255), TRUE);
}

//���ݑ_���ׂ��e�̔ԍ���Ԃ�
int GetTargetBallNum(CBall* balls) {
	for (int i = 1; i < BALL_NUM; i++) {
		if (balls[i].GetFallFlag() == false) {
			return i;
		}
	}
	return 0;
}

//�~�̕`��
void DrawCircleOnPlane(VECTOR center,float radius,int divnum,unsigned int color) {

	VECTOR v = VGet(radius, 0.0f, 0.0f);
	MATRIX rotate = MGetRotZ(DX_PI_F*2 / divnum);

	for(int i = 0; i < divnum; i++) {
		VECTOR nextv = VTransform(v, rotate);

		DrawLine3D(VAdd(center, v), VAdd(center, nextv),color);

		v = nextv;
	}
}

//�V���b�g����
void ShotProcess(CBall * balls,CWall * walls,CHole* holes) {
	if (CheckBallStop(balls)) {

		//������ʂ������Ă���Ĕz�u
		if (balls[0].GetFallFlag()) {
			balls[0].FallRecover();
			balls[0].SetPosition(VGet(0.0f, -65.0f, 0.0f));
		}

		//�_���ׂ�����\��
		DrawCircleOnPlane(balls[GetTargetBallNum(balls)].GetPosition(), BALL_RAD * 2, 36, GetColor(255, 255, 0));

		VECTOR shotVector = CalcShotVector(balls);	//�V���b�g�����̎Z�o

		//�\�����̕\��
		Predicter.HitPredict(balls, BALL_NUM, walls, WALL_NUM, holes,HOLE_NUM,balls[0].GetPosition(), shotVector);

		//�N���b�N������V���b�g
		if (GetMouseInput() == MOUSE_INPUT_LEFT) {
			balls[0].AddPower(VScale(shotVector, 0.1f));
			shotVector = VScale(shotVector, 0.001f);
		}

		DrawCue(balls[0].GetPosition(), shotVector);	//�L���[�̕`��
	}
}



//���C��
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetFullSceneAntiAliasingMode(4, 2);
	SetGraphMode(960,540,32);	// �E�B���h�E�T�C�Y�̐ݒ�
	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ɐݒ�
							
	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		// �G���[�����������璼���ɏI��
		return -1;
	}

	//�O���t�B�b�N�֘A�̏����ݒ�
	GlaphicsInit();

	//�{�[���̔z�u
	CBall balls[BALL_NUM];
	NineBallInit(balls);

	//�ǂ̔z�u
	CWall walls[WALL_NUM];
	WallInit(walls);

	//���̔z�u
	CHole holes[HOLE_NUM];
	HoleInit(holes);


	//���C�����[�v
	while (!ScreenFlip() && !ClearDrawScreen() && !ProcessMessage()) {
		

		//�S�Ă̕ǂ̕`��(��)
		for (int i = 0; i < WALL_NUM; i++) {
			walls[i].Draw();
		}

		//�S�Ă̌��̕`��
		for (int i = 0; i < HOLE_NUM; i++) {
			holes[i].Draw();
		}

		//�S�Ẵ{�[���̏Փˏ����C�X�V�C�`��
		for (int i = 0; i < BALL_NUM; i++) {
			balls[i].HitBall(balls,BALL_NUM);
			balls[i].HitWall(walls, WALL_NUM);
			balls[i].FallinHole(holes, HOLE_NUM);
			balls[i].Update();
			balls[i].Draw();
		}

		//�V���b�g����
		ShotProcess(balls, walls, holes);
		
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}