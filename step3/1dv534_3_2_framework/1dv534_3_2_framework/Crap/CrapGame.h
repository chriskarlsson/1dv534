// CrapGame.h

#ifndef CRAPGAME_H
#define CRAPGAME_H

#include <cstdlib>
#include <ctime>


class CrapGame {
public:
	CrapGame() : _rnd(1, 6) {}
	virtual int play(char* bet, int amount);		// Place amount money on position bet and return winnings
	virtual int getID() const { 
		return CRAP_ID; 
	}
private:
	static const int CRAP_ID = 124578;				// This is a unique number assigned to the Crap game
	
	class Randomizer {								// Inner nested class...
	public:
		Randomizer(int min, int max) : _min(min), _max(max) {
			srand( (unsigned)time( NULL ) );  
		}

		int getNumber() {
			return ( rand() % (_max -_min + 1) ) + _min; 
		}
	private:
		int _min, _max;
	} _rnd;	// Creates an object of Randomizer class ('_rnd' is used in method play() in CrapGame.cpp)

};

#endif