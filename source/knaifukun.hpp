
#ifndef __KNAIFU_KUN_H__
#define __KNAIFU_KUN_H__

#include <gctypes.h>

class KnaifuKun {
public:
	static void init(void);
	static void deinit(void);

	void update(void);
	void draw(void);

	KnaifuKun();
	~KnaifuKun();

	void resetPos(void);

public:
	u16 x;
	u16 y;

	u16 r;

	bool shooting = false;
};

#endif