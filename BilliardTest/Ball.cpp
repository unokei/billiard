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

//�X�V
void CBall::Update() {
	//�{�[���̈ʒu�X�V
	position = VAdd(position, power);	//�̓x�N�g�������Ɉړ�

	//�{�[���̗͂̌���
	power = VScale(power, 0.99f);		//1f���Ƃ�1%�͂������i�����I�ɂ͐������Ȃ��j
	if (VSize(power) < 0.01f) {
		power = VGet(0.f, 0.f, 0.f);	//���ȉ��̑��x�̎��Ɋ��S��~
	}
}

void CBall::Draw() {
	//����`��
	DrawSphere3D(position, radius, 32, color, GetColor(255, 255, 255), TRUE);

	//���ۂ̓{�[���̃��f����`�悵����
}

//�ʒu�̐ݒ�
void CBall::SetPosition(VECTOR pos) {
	position = pos;
}

//�ʒu�̎擾
VECTOR CBall::GetPosition() {
	return position;
}

//�͂̎擾
VECTOR CBall::GetPower() {
	return power;
}

//�͂�������
void CBall::AddPower(VECTOR addpower) {
	power = VAdd(power, addpower);
}

//�{�[���ƂԂ���(�{�[���̔z��A�h���X�C�{�[���̐�)
void CBall::HitBall(CBall *hitBall,int length) {

	//�S�{�[����T��
	for (int i = 0; i < length; i++) {

		//�����ȊO�̃{�[����������
		if (hitBall != this) {
			VECTOR distVect = VSub(hitBall->GetPosition(), position);	//�����ƑΏۂ̒��S���狗���x�N�g�����Z�o

			//���������a*2�ȉ��Ȃ�ڐG(�S�{�[���̔��a�͓���T�C�Y����)
			if (VSize(distVect) <= radius * 2) {
				float dot = VDot(power, VNorm(distVect));	//�̓x�N�g���ƐڐG�x�N�g���i���K�������x�N�g���j�̓���

				//���ς�0�ȏ�i�ڐG���s�p�j�������ꍇ,�ڐG�Ώۂɗ͂�������
				if (dot > 0) {
					VECTOR addPower = VScale(VNorm(distVect), VDot(power, VNorm(distVect)));	//�^�����(�̓x�N�g���̐ڐG��������)
					hitBall->AddPower(addPower);	//�^����͂�Ώۂɉ�����
					power = VSub(power, addPower);	//�^�����������͂�����
				}
			}
		}
		hitBall++;
	}
}

//�ǂƂԂ���
void CBall::HitWall(CWall *wall, int length) {
	//�S�ǒT��
	for (int i = 0; i < length; i++) {
		float distance = Segment_Point_MinLength(wall->GetStartPoint(), wall->GetEndPoint(), position);	//�ǂƋ��̒��S�Ƃ̋���

		//���������a�ȉ��Ȃ�ڐG
		if (distance <= radius) {
			float dot = VDot(power, wall->GetNormVector());	//�̓x�N�g���ƐڐG�x�N�g���i���K�������x�N�g���j�̓���

			//���ς�0�ȉ��i�݊p�j�������ꍇ�C���˂���
			if (dot < 0) {
				VECTOR addPower = VScale(VScale(wall->GetNormVector(),-1), VDot(power, VScale(wall->GetNormVector(), -1)));	//�^�����(�̓x�N�g���̐ڐG��������)
				power = VSub(power, VScale(addPower, 2));
			}
		}
		wall++;
	}
}