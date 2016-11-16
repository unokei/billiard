#include "DxLib.h"
#include "Ball.h"
#include "Wall.h"

#define BALL_NUM 10
#define BALL_RAD 5.7f / 2.0f
#define WALL_NUM 4
#define ROOT3 1.73205080757f

//ナインボールの初期配置
void NineBallInit(CBall* balls) {

	float x = 0;
	float y = 55.0f;
	float z = 0;

	float placerad = BALL_RAD + 0.1f;
	float tatehaba = ROOT3 * placerad;

	//手玉
	balls[0] = CBall(0, GetColor(220, 220, 200)	, BALL_RAD, VGet(x					, y - 120.0f		, z));

	//的球
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

//壁の配置
void WallInit(CWall* walls) {
	float narrowSide = 125.0f;
	float longSide = 220.0f;
	VECTOR basePoint = VGet(narrowSide * (-0.5f), longSide * ( - 0.5f), 0.0f);

	walls[0] = CWall(basePoint, VAdd(basePoint,VGet(0,longSide,0)));
	walls[1] = CWall(VAdd(basePoint, VGet(0, longSide, 0)), VAdd(basePoint, VGet(narrowSide, longSide, 0)));
	walls[2] = CWall(VAdd(basePoint, VGet(narrowSide, longSide, 0)), VAdd(basePoint, VGet(narrowSide, 0, 0)));
	walls[3] = CWall(VAdd(basePoint, VGet(narrowSide, 0, 0)), basePoint);
}

//描画，カメラ，ライトなどの設定
void GlaphicsInit() {
	SetDrawScreen(DX_SCREEN_BACK);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	//カメラの位置角度設定
	SetCameraPositionAndTargetAndUpVec(VGet(0.0f, 0.0f, -180.0f), VGet(0.0f, 0.0f, 0.0f), VGet(-1.0f, 0.0f, 0.0f));

	//カメラ設定
	//SetupCamera_Ortho(300.0f);
	SetupCamera_Perspective(1.0472f);

	ChangeLightTypePoint(VGet(0.0f, 0.0f, -2000.0f), 2500.0f, 0.0f, 0.0006f, 0.0f);
	SetGlobalAmbientLight(GetColorF(1.0f, 0.9f, 0.5f, 0.0f));

}

//空間中のマウス座標の取得
VECTOR GetMousePos() {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	VECTOR startP = ConvScreenPosToWorldPos(VGet((float)mouseX, (float)mouseY, 0.0f));	//マウスのワールド座標（奥行0）
	VECTOR endP = ConvScreenPosToWorldPos(VGet((float)mouseX, (float)mouseY, 1.0f));		//マウスのワールド座標（奥行最大）
	VECTOR ray = VNorm(VSub(endP, startP));	//マウスへのレイ

	float scale = (0.0f - startP.z) / ray.z;
	VECTOR worldP = VAdd(startP, VScale(ray, scale));	//レイのzが0.0の座標を算出

	return worldP;
}

//全ボールの停止をチェック
bool CheckBallStop(CBall *balls) {
	for (int i = 0; i < BALL_NUM; i++) {
		if (VSize(balls[i].GetPower()) != 0.0f) {
			return false;
		}
	}
	return true;
}

//ショットベクトルの算出
VECTOR CalcShotVector(CBall * cueball) {
	VECTOR worldP = GetMousePos();

	float shotmax = 50.0f;

	float cuedist = VSize(VSub(worldP, cueball->GetPosition()));
	if (cuedist > shotmax) cuedist = shotmax;

	VECTOR shotVector = VScale(VNorm(VSub(cueball->GetPosition(), worldP)), cuedist);

	return shotVector;
}

//キューの描画
void DrawCue(VECTOR ballpos,VECTOR shotvect) {
	float cuelong = 100.0f;

	VECTOR cueVector = VScale(shotvect,-1);

	VECTOR cueStartPos = VAdd(ballpos, cueVector);
	VECTOR cueEndPos = VAdd(cueStartPos,VScale(VNorm(cueVector),cuelong));

	//描画　とりあえずカプセルで代用
	DrawCapsule3D(cueStartPos, cueEndPos, 1.0f, 8, GetColor(70, 20, 0), GetColor(255, 255, 255), TRUE);
}

//ショット処理
void ShotProcess(CBall * balls) {
	if (CheckBallStop(balls)) {
		VECTOR shotVector = CalcShotVector(balls);	//ショット方向の算出

		//クリックしたらショット
		if (GetMouseInput() == MOUSE_INPUT_LEFT) {
			balls[0].AddPower(VScale(shotVector, 0.1f));
			shotVector = VScale(shotVector, 0.001f);
		}

		DrawCue(balls[0].GetPosition(), shotVector);	//キューの描画
	}
}

//メイン
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(960,540,32);	// ウィンドウサイズの設定
	ChangeWindowMode(TRUE);		// ウィンドウモードに設定
							
	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return -1;
	}

	//グラフィック関連の初期設定
	GlaphicsInit();

	//ボールの配置
	CBall balls[BALL_NUM];
	NineBallInit(balls);

	//壁の配置
	CWall walls[WALL_NUM];
	WallInit(walls);
		

	//メインループ
	while (!ScreenFlip() && !ClearDrawScreen() && !ProcessMessage()) {

		//全ての壁の描画(仮)
		for (int i = 0; i < WALL_NUM; i++) {
			walls[i].Draw();
		}

		//全てのボールの衝突処理，更新，描画
		for (int i = 0; i < BALL_NUM; i++) {
			balls[i].HitBall(balls,BALL_NUM);
			balls[i].HitWall(walls, WALL_NUM);
			balls[i].Update();
			balls[i].Draw();
		}

		//ショット処理
		ShotProcess(balls);
	}



	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}