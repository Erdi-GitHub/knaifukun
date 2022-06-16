#include "wood.hpp"

#include "knaifukun.hpp"
#include <grrlib.h>

#include "wood_png.h"
#include "knaifukun_stabbed_png.h"

#include <math.h>

static GRRLIB_texImg *s_texture;
static GRRLIB_texImg *s_knaifukun;

static u16 s_seed;

void Wood::init(void) {
	s_texture = GRRLIB_LoadTexturePNG(wood_png);

	GRRLIB_SetMidHandle(s_texture, true);

	s_knaifukun = GRRLIB_LoadTexturePNG(knaifukun_stabbed_png);
}

void Wood::deinit(void) {
	GRRLIB_FreeTexture(s_texture);
	GRRLIB_FreeTexture(s_knaifukun);
}

void Wood::draw(void) {
	u16 x = rmode->fbWidth >> 1;
	u16 y = (s_texture->h >> 1) + 5;

	constexpr f32 scale = .7;

	for(u16 r : knaifuDegs)
		GRRLIB_DrawImg(x, y, s_knaifukun, r + rotation, .5, .5, 0xffffffff);
	
	GRRLIB_DrawImg(x, y, s_texture, rotation, scale, scale, 0xffffffff);
}
void Wood::update(void) {
	rotation += 4;
	rotation %= 360;

	s_seed += 1935;
}

void Wood::resetWood(u8 randomDegAmount) {
	knaifuDegs.clear();

	if(randomDegAmount) {
		for(u8 i = 0; i < randomDegAmount; i++) {
			knaifuDegs.push_back(((f32)(s_seed + (i * 3)) / UINT16_MAX) * 360);
		}
	}
}

bool Wood::addDeg(void) {
	u16 v = 360 - rotation + 70;
	
	for(u16 r : knaifuDegs) {
		if(abs(v - r) < 15)
			return false;
	}

	knaifuDegs.push_back(v);
	return true;
}

Wood::Wood() {
	
}

Wood::~Wood() {
	
}
