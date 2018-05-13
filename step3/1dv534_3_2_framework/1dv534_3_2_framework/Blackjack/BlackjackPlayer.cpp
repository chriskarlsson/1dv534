/**********************************************************************/
// File:	BlackjackPlayer.cpp
// Summary: The player used for playing BlackjackGame.cpp.
// Version:	0.0
// Owner:	Christoffer Karlsson
// -------------------------------------------
// Log:     2018-04-06 File created by Christoffer
/**********************************************************************/

// Preprocessor directives
#include <iostream>
#include "UserInput.h"
#include "BlackjackPlayer.h"

using std::bad_alloc;
using std::cin;
using std::cout;
using std::endl;

//-----------------------------------------------------------------
// bool setGame(IGame* game)
//
// Summary: Sets the specific game for this player to play.
// Returns: True if execution was correct and otherwise false.
//-----------------------------------------------------------------
bool BlackjackPlayer::setGame(IGame* game)
{
    if (game->getID() != CRAP_ID)
    {
        return false;
    }

    if (_game != nullptr && _game != game)
    {
        delete _game;
    }

    _game = game;

    return true;
}

//-----------------------------------------------------------------
// bool play(int numberOfTimes)
//
// Summary: Place amount money on position bet and return winnings.
// Returns: True if execution was correct and otherwise false.
//-----------------------------------------------------------------
bool BlackjackPlayer::play(int numberOfTimes)
{
    for (int count = 1; count <= numberOfTimes; ++count)
    {
        auto bet = _placeBet();
        auto win = _game->play(nullptr, bet);
        _money += win;

        _printScore(win);

        // Explain why the game ended
        if (_money <= 0)
        {
            cout << "You are out of money. Game over." << endl;
            return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------
// int _placeBet()
//
// Summary: Asks user how much to bet
// Returns: The bet as an integer
//-----------------------------------------------------------------
int BlackjackPlayer::_placeBet()
{
    while (true)
    {
        // Ask user how much to bet
        int bet = getIntegerFromUser("How much to bet?");

        // Make sure user has enough markers
        if (bet > _money)
        {
            cout << "Player only has " << _money << endl;
        }
        else
        {
            // Move markers from markers to bet
            _money -= bet;
            ++_betCount;
            return bet;
        }
    }
}

//-----------------------------------------------------------------
// void _printScore(int win) const
//
// Summary: Prints the players score
// Returns: -
//-----------------------------------------------------------------
void BlackjackPlayer::_printScore(int win) const
{
    const char *WIN_STRING = " Win: ";
    const char *TOT_STRING = " Tot:";

    // Print win
    cout << WIN_STRING << win << endl;

    // Print markers
    cout << TOT_STRING << _money << endl;
}