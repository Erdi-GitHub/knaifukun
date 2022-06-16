
#ifndef __WOOD_H__
#define __WOOD_H__

#include <gctypes.h>
#include <vector>
#include "knaifukun.hpp"

class Wood {
private:
	u16 rotation; /** deg */
	std::vector<u16> knaifuDegs;
public:
	static void init(void);
	static void deinit(void);

	void update(void);
	void draw(void);

	bool addDeg(void);

	void resetWood(u8 randomDegAmount = 0);

	Wood();
	~Wood();
};

#endif
