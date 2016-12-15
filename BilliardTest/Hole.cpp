#include "Hole.h"



CHole::CHole()
{
	center = VGet(0.0, 0.0, 0.0);
	radius = 1.0f;
}

CHole::CHole(VECTOR c, float r)
{
	center = c;
	radius = r;
}


CHole::~CHole()
{
}

//’†SÀ•W‚Ìæ“¾
VECTOR CHole::GetCenter() {
	return center;
}

//”¼Œa‚Ìæ“¾
float CHole::GetRaidus() {
	return radius;
}

void CHole::Draw() {
	DrawCircleOnPlane(center, radius, 16, GetColor(255, 255, 255));
}

void CHole::DrawCircleOnPlane(VECTOR center, float radius, int divnum, unsigned int color) {

	VECTOR v = VGet(radius, 0.0f, 0.0f);
	MATRIX rotate = MGetRotZ(DX_PI_F * 2 / divnum);

	for (int i = 0; i < divnum; i++) {
		VECTOR nextv = VTransform(v, rotate);

		DrawLine3D(VAdd(center, v), VAdd(center, nextv), color);

		v = nextv;
	}
}
