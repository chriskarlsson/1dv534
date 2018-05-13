// CrapGame.cpp

#include "CrapGame.h"


int CrapGame::play(char* bet, int amount)
{
	int nr1 = _rnd.getNumber() + _rnd.getNumber();

	if (nr1 == 7 || nr1 == 11)
		return 2 * amount;
	if (nr1 == 2 || nr1 == 3 || nr1 == 12)
		return 0;

	while (true) {
		int nr2 = _rnd.getNumber() + _rnd.getNumber();

		if (nr2 == nr1)
			return 2 * amount;
		if (nr2 == 7)
			return 0;
	}
}


