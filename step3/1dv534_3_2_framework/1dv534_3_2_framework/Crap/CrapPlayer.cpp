// CrapPlayer.cpp

#include "CrapPlayer.h"


bool CrapPlayer::setGame(IGame* gamep)	// Sets the specific game for this player to play
{
	if (gamep->getID() != CRAP_ID)	
		return false;				// If the game specified is other than Crap - return error

	if (_gamep != NULL && _gamep != gamep) 
		delete _gamep;				// If occupied by other game and not equal - delete it

	_gamep = gamep;
	return true;
}


bool CrapPlayer::play(int numberOfTimes)	// Tells player to play the game numberOfTimes times
{
	const int BETSIZE = 1;

	for (int count = 1; count <= numberOfTimes; ++count) {

		if (_money - BETSIZE < 0)			// If no money left...
			return false;

		_money += _gamep->play(NULL, BETSIZE) - BETSIZE;
		++_betCount;
	}
	return true;
}


