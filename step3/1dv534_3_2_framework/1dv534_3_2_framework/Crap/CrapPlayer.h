// CrapPlayer.h

#ifndef CRAPPLAYER_H
#define CRAPPLAYER_H
#include <cstdlib>

#include "IPlayer.h"
#include "IGame.h"


class CrapPlayer : public IPlayer {
public:
	CrapPlayer(int money) : _gamep(NULL), _money(money), _betCount(0), CRAP_ID(124578) {}
	virtual bool setGame(IGame* game);		// Gives the player a game object to use
	virtual bool play(int numberOfTimes);	// Tells player to play the game numberOfTimes times

	virtual int	getMoney() const {				// Returns the amount of money still available for game
		return _money;
	}

	virtual int getBetCount() const {			// Returns the total number of bets placed during object life time
		return _betCount;
	}

private:
	IGame* _gamep;								// Points out the game to use (should be a Crap Game)
	int	_money;									// Shows the current amount of money available for playing
	int	_betCount;								// Shows the number of bets placed so far
	const int CRAP_ID;							// ID assigned to the Crap game
};

#endif