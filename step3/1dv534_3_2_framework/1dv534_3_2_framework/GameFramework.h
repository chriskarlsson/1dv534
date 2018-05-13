// Preprocessor directives
#include <iostream> // cin, cout, endl
#include "IGame.h"
#include "IPlayer.h"
#include "BlackjackPlayer.h"
#include "BlackjackGame.h"

// Usings
using std::cin;
using std::cout;

class GameFramework {
public:
    GameFramework(IPlayer* player, IGame* game) : _player(player), _game(game) {}
    ~GameFramework() = default;
    inline int run(int numberOfTimes);
private:
    IPlayer * _player;
    IGame*   _game;
};

//-----------------------------------------------------------------
// int run(int numberOfTimes)
//
// Summary: Plays the selected game and prints the result
// Returns: -
//-----------------------------------------------------------------
inline int GameFramework::run(int numberOfTimes)
{
    _player->setGame(_game);
    _player->play(numberOfTimes);
    std::cout << "After " << _player->getBetCount() << " turns, the player has: " << _player->getMoney() << " money left." << std::endl;
    cout << "Press enter to continue ...";
    cin.get();
    return 0;
}