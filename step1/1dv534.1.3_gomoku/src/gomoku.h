#ifndef GOMOKU_H
#define GOMOKU_H

#include <TakeFive.h>
#include <menu.h>

class Gomoku {
public:
    Gomoku();
    ~Gomoku();
    int run();
private:
    const Menu * _MENU;
    Player _player;
    Player _computer;
    int _boardWidth;
    int _boardHeight;
    const int _MIN_BOARD_SIZE = 5;
    bool _playerToDoNextMove;
    void _setupMenu();
    template <class T>
    T _getAplphaNumFromUser(const char *question, T min, T max);
    bool _userYesOrNo(const char *question);
    void _setStartPlayer();
    void _setXorO();
    void _setBoardSize();
    Player _play();
    void _showResult(Player winner);
    void _getPosition(int & row, char & column);
};

#endif // GOMOKU_H
