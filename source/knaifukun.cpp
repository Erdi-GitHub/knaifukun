#include "knaifukun.hpp"

#include "knaifukun_png.h"
#include <grrlib.h>

static GRRLIB_texImg *s_knaifu;

void KnaifuKun::init(void) {
	s_knaifu = GRRLIB_LoadTexturePNG(knaifukun_png);
	GRRLIB_SetMidHandle(s_knaifu, true);
}
void KnaifuKun::deinit(void) {
	GRRLIB_FreeTexture(s_knaifu);
}

void KnaifuKun::draw(void) {
	GRRLIB_DrawImg(x, y, s_knaifu, 90, .5, .5, 0xffffffff);
}
void KnaifuKun::update(void) {
	if(shooting)
		y -= 20;
}

void KnaifuKun::resetPos(void) {
	x = rmode->fbWidth >> 1;
	y = rmode->xfbHeight - (s_knaifu->h >> 1) - 25;
}

KnaifuKun::KnaifuKun() {
	resetPos();
}
KnaifuKun::~KnaifuKun() {}
