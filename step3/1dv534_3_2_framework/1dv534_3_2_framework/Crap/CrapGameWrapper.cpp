/**********************************************************************/
// File:	CrapGameWrapper.cpp
// Summary: A wrapper class making CrapGame addher to IGame interface.
// Version:	0.0
// Owner:	Christoffer Karlsson
// -------------------------------------------
// Log:     2018-04-06 File created by Christoffer
/**********************************************************************/

// Preprocessor directives
#include "CrapGameWrapper.h"

//-----------------------------------------------------------------
// CrapGameWrapper()
//
// Summary: Constructor
// Returns: -
//-----------------------------------------------------------------
CrapGameWrapper::CrapGameWrapper()
{
    _game = new CrapGame();
}

//-----------------------------------------------------------------
// ~CrapGameWrapper()
//
// Summary: Destructor
// Returns: -
//-----------------------------------------------------------------
CrapGameWrapper::~CrapGameWrapper()
{
    delete _game;
}

//-----------------------------------------------------------------
// int play(char* bet, int amount)
//
// Summary: Place amount money on position bet and return winnings
// Returns: The amount that was won.
//-----------------------------------------------------------------
int CrapGameWrapper::play(char* bet, int amount)
{
    return _game->play(bet, amount);
}


