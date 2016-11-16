#include "Ball.h"


CBall::CBall()
{
	number = -1;
	color = GetColor(150,150,150);
	radius = 10.0f;
	power = VGet(0.f, 0.f, 0.f);
}

CBall::CBall(int n, unsigned int c , float r)
{
	number = n;
	color = c;
	radius = r;
	power = VGet(0.f, 0.f, 0.f);
}

CBall::CBall(int n,unsigned int c, float r, VECTOR pos)
{
	number = n;
	color = c;
	radius = r;
	position = pos;
	power = VGet(0.f, 0.f, 0.f);
}


CBall::~CBall()
{
}

//更新
void CBall::Update() {
	//ボールの位置更新
	position = VAdd(position, power);	//力ベクトル方向に移動

	//ボールの力の減衰
	power = VScale(power, 0.99f);		//1fごとに1%力を失う（物理的には正しくない）
	if (VSize(power) < 0.01f) {
		power = VGet(0.f, 0.f, 0.f);	//一定以下の速度の時に完全停止
	}
}

void CBall::Draw() {
	//球を描画
	DrawSphere3D(position, radius, 32, color, GetColor(255, 255, 255), TRUE);

	//実際はボールのモデルを描画したい
}

//位置の設定
void CBall::SetPosition(VECTOR pos) {
	position = pos;
}

//位置の取得
VECTOR CBall::GetPosition() {
	return position;
}

//力の取得
VECTOR CBall::GetPower() {
	return power;
}

//力を加える
void CBall::AddPower(VECTOR addpower) {
	power = VAdd(power, addpower);
}

//ボールとぶつかる(ボールの配列アドレス，ボールの数)
void CBall::HitBall(CBall *hitBall,int length) {

	//全ボールを探索
	for (int i = 0; i < length; i++) {

		//自分以外のボールだった時
		if (hitBall != this) {
			VECTOR distVect = VSub(hitBall->GetPosition(), position);	//自分と対象の中心から距離ベクトルを算出

			//距離が半径*2以下なら接触(全ボールの半径は同一サイズ扱い)
			if (VSize(distVect) <= radius * 2) {
				float dot = VDot(power, VNorm(distVect));	//力ベクトルと接触ベクトル（正規化距離ベクトル）の内積

				//内積が0以上（接触が鋭角）だった場合,接触対象に力を加える
				if (dot > 0) {
					VECTOR addPower = VScale(VNorm(distVect), VDot(power, VNorm(distVect)));	//与える力(力ベクトルの接触方向成分)
					hitBall->AddPower(addPower);	//与える力を対象に加える
					power = VSub(power, addPower);	//与えた分だけ力を失う
				}
			}
		}
		hitBall++;
	}
}

//壁とぶつかる
void CBall::HitWall(CWall *wall, int length) {
	//全壁探索
	for (int i = 0; i < length; i++) {
		float distance = Segment_Point_MinLength(wall->GetStartPoint(), wall->GetEndPoint(), position);	//壁と球の中心との距離

		//距離が半径以下なら接触
		if (distance <= radius) {
			float dot = VDot(power, wall->GetNormVector());	//力ベクトルと接触ベクトル（正規化距離ベクトル）の内積

			//内積が0以下（鈍角）だった場合，反射する
			if (dot < 0) {
				VECTOR addPower = VScale(VScale(wall->GetNormVector(),-1), VDot(power, VScale(wall->GetNormVector(), -1)));	//与える力(力ベクトルの接触方向成分)
				power = VSub(power, VScale(addPower, 2));
			}
		}
		wall++;
	}
}