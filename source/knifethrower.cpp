
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <grrlib.h>
#include <cstdio>

#include "knaifukun.hpp"
#include "wood.hpp"
#include "OpenSans_ExtraBold_ttf.h"

#include <bits/stdc++.h>

#include "woosh_mp3.h"

#include <asndlib.h>
#include <mp3player.h>

#define CLAMP(x, min, max) (x < min ? min : (x > max ? max : x))

int main(void) {
	u32 score = 0;
	u8 lives = 5;
	u8 level = 0;

	u32 lastScore = 0;

	GRRLIB_Init();
	WPAD_Init();
	
	ASND_Init();
	MP3Player_Init();

	KnaifuKun::init();
	Wood::init();

	Wood wood;
	KnaifuKun *knaifu = new KnaifuKun();

	GRRLIB_ttfFont *font = GRRLIB_LoadTTF(OpenSans_ExtraBold_ttf, OpenSans_ExtraBold_ttf_size);

	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_DATA_ACCEL);

	while(!WPAD_BatteryLevel(0)) {
		WPAD_ScanPads();
		GRRLIB_PrintfTTF(20, 30, font, "Connect WiiPad 1", 15, 0xff000000);
		GRRLIB_Render();
	}

	gforce_t gforce;

	while(1) {
		WPAD_ScanPads();
		WPAD_GForce(0, &gforce);

		if(!knaifu->shooting && (WPAD_ButtonsDown(0) & WPAD_BUTTON_A || (gforce.x > 2 || gforce.y > 2 || gforce.z > 2))) {
			knaifu->shooting = true;
			MP3Player_PlayBuffer(woosh_mp3, woosh_mp3_size, NULL);
		}

		if(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)
			do {
				WPAD_ScanPads();

				if(WPAD_ButtonsDown(0) & WPAD_BUTTON_A)
					goto byebye;

				GRRLIB_FillScreen(0x0000ffff);
				GRRLIB_PrintfTTF(10, 10, font, "Exit with [A]", 15, 0xffffff00);
				GRRLIB_PrintfTTF(10, 25, font, "Restart with the [Home] button", 15, 0xffffff00);

				GRRLIB_Render();
			} while(!(WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME));
			

		GRRLIB_FillScreen(0xffffffff);

		knaifu->update();
		knaifu->draw();

		wood.update();
		wood.draw();

		if(knaifu->y < 180) {
			knaifu->resetPos();
			knaifu->shooting = false;

			if(!wood.addDeg()) {
				if(lives-- == 0) {
					wood.resetWood();

					do {
						WPAD_ScanPads();

						GRRLIB_PrintfTTF(10, 20, font, "You've lost! Press plus [+] to retry.", 15, 0xff000000);
						GRRLIB_PrintfTTF(10, 45, font, ("Points: " + std::to_string(score)).c_str(), 15, 0x00ff0000);
						GRRLIB_PrintfTTF(10, 70, font, ("Level: " + std::to_string(level)).c_str(), 15, 0x00ff0000);

						GRRLIB_Render();
					} while(!(WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS));
					

					lives = 5;
					lastScore = level = score = 0;
				}
			} else
				score++;
			
			if(score == lastScore + (u16)CLAMP(level * 2, 3, 15)) {
				level++;
				lastScore = score;

				lives = 5;

				wood.resetWood(level < 2 ? 0 : CLAMP(level, 3, 5));
			}
		}

		GRRLIB_PrintfTTF(10, 35, font, ("Points: " + std::to_string(score)).c_str(), 15, 0x00ff0000);
		GRRLIB_PrintfTTF(10, 60, font, ("Level: " + std::to_string(level)).c_str(), 15, 0x00ff0000);
		GRRLIB_PrintfTTF(10, 85, font, ("Lives: " + std::to_string(lives)).c_str(), 15, 0x00ff0000);

		GRRLIB_Render();
	}

	goto byebye;

byebye:
	KnaifuKun::deinit();
	Wood::deinit();

	GRRLIB_FreeTTF(font);

	GRRLIB_Exit();

	exit(0);
}

