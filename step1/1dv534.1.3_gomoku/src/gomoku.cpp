//-----------------------------------------------------------------------------
// File:    gomoku.cpp
// Summary: Plays a game of Gomoku a.k.a. Five in a row
// Version: 0.0
// Owner:   Christoffer Karlsson
//-----------------------------------------------------------------------------
// Log:   2018-04-08 File created by Christoffer
//
//-----------------------------------------------------------------------------

// Preprocessor directives
#include <iostream> // cin and cout
#include <gomoku.h>

// OS specific adjustments
#ifdef _WIN32
    // Windows
    #define CLEARSCREEN system("cls")
#elif __APPLE__
    // Mac OS
    #define CLEARSCREEN system("clear")
#elif __linux__
    // Linux
    #define CLEARSCREEN system("clear")
#else
   error "Unknown compiler"
#endif

// Constants
const int MAX_READ_INPUT_LENGTH = 100;

// Usings
using std::cin;
using std::cout;
using std::endl;

//-----------------------------------------------------------------------------
// Gomoku()
//
// Summary: Constructor. Sets up defaults to enable a game to be initiated
//          directly.
// Returns: -
//-----------------------------------------------------------------------------
Gomoku::Gomoku()
{
    _setupMenu();
    _boardWidth = _MIN_BOARD_SIZE;
    _boardHeight = _MIN_BOARD_SIZE;
    _player = CROSS;
    _computer = RING;
    _playerToDoNextMove = true;
}

//-----------------------------------------------------------------------------
// ~Gomoku()
//
// Summary: Destructor. Releases the dynamic memory allocated by the
//          constructor.
// Returns: -
//-----------------------------------------------------------------------------
Gomoku::~Gomoku()
{
    delete _MENU;
}

//-----------------------------------------------------------------------------
// int run()
//
// Summary: Displays the menu to allow the user to setup the game as desired
//          or to play the game.
// Returns: 0 when user stops execution by menu selection.
//-----------------------------------------------------------------------------
int Gomoku::run()
{
    while (true)
    {
        auto choice = _MENU->getMenuSelection();

        switch(choice)
        {
            case 1:
                _setStartPlayer();
                break;
            case 2:
                _setXorO();
                break;
            case 3:
                _setBoardSize();
                break;
            case 4:
            {
                auto winner = _play();
                _showResult(winner);
            }
                break;
            case 5:
                return 0;
        }
    }
}

//-----------------------------------------------------------------------------
// void _setupMenu()
//
// Summary: Adds menu options to _MENU.
// Returns: -
//-----------------------------------------------------------------------------
void Gomoku::_setupMenu()
{
    const int NUMBER_OF_ITEMS = 5;
    const char * HEADER = "Welcome to Take Five\n---------------------\nWhat do you want to do?";
    const char ** MENU_ITEMS = new const char*[NUMBER_OF_ITEMS];
    MENU_ITEMS[0] = "Choose if you (default) or the computer should start";
    MENU_ITEMS[1] = "Choose if you should play as \"X\" (default) or \"O\"";
    MENU_ITEMS[2] = "Choose how large the board should be";
    MENU_ITEMS[3] = "Start the game";
    MENU_ITEMS[4] = "End the game";

    _MENU = new Menu(HEADER, MENU_ITEMS, NUMBER_OF_ITEMS);
}

//-----------------------------------------------------------------------------
// T _getAplphaNumFromUser(const char *question, T min, T max)
//
// Summary: Poses a question to the user.
// Returns: The answer of type T within min and max.
//-----------------------------------------------------------------------------
template <class T>
T Gomoku::_getAplphaNumFromUser(const char *question, T min, T max)
{
    T value;

    while (true)
    {
        // Pose question and read the answer
        cout << question << " (" << min << "-" << max << "): ";
        cin >> value;

        if (cin.fail() || value > max || value < min)
        {
            // Explain what went wrong
            cout << "Invalid input. Input should be between " << min << " and " << max << "." << endl;
            // Clear error
            cin.clear();
            // Clear input (this has to be done after error clearing)
            cin.ignore(MAX_READ_INPUT_LENGTH, '\n');
        }
        else
        {
            // Clear input
            cin.ignore(MAX_READ_INPUT_LENGTH, '\n');
            return value;
        }
    }
}

//-----------------------------------------------------------------------------
// bool userYesOrNo(char *question)
//
// Summary: Asks the user the supplied question.
// Returns: True if the answer isn't n or N.
//-----------------------------------------------------------------------------
bool Gomoku::_userYesOrNo(const char *question)
{
    char input[MAX_READ_INPUT_LENGTH];

    // Ask the user if program should re-run and read input
    cout << endl << question << " (Y/n): ";
    cin.getline(input, MAX_READ_INPUT_LENGTH);
    cout << endl;

    // Check if answer is negative
    auto answer = toupper(input[0]) != 'N';

    return answer;
}

//-----------------------------------------------------------------------------
// void _setStartPlayer()
//
// Summary: Asks the user if he/she or the computer should start playing and
//          sets _playerToDoNextMove accordingly.
// Returns: -
//-----------------------------------------------------------------------------
void Gomoku::_setStartPlayer()
{
    CLEARSCREEN;
    _playerToDoNextMove = _userYesOrNo("Should you start the game?");
}

//-----------------------------------------------------------------------------
// void _setXorO()
//
// Summary: Asks the user if he/she should play as X or O and sets _player and
//          _computer accordingly.
// Returns: -
//-----------------------------------------------------------------------------
void Gomoku::_setXorO()
{
    CLEARSCREEN;
    if (_userYesOrNo("Do you want to play as cross?"))
    {
        _player = CROSS;
        _computer = RING;
    }
    else
    {
        _player = RING;
        _computer = CROSS;
    }
}

//-----------------------------------------------------------------------------
// void _setBoardSize()
//
// Summary: Asks the user for the wanted board size which should be within
//          _MIN_BOARD_SIZE and 25 ('z' - 'a') in each direction.
// Returns: -
//-----------------------------------------------------------------------------
void Gomoku::_setBoardSize()
{
    int maxSize = 'z' - 'a';
    CLEARSCREEN;
    _boardWidth = _getAplphaNumFromUser<unsigned int>("Please enter board width",
                                                      _MIN_BOARD_SIZE,
                                                      maxSize);
    _boardHeight = _getAplphaNumFromUser<unsigned int>("Please enter board height",
                                                       _MIN_BOARD_SIZE,
                                                       maxSize);
}

//-----------------------------------------------------------------------------
// Player _play()
//
// Summary: Creates a new game of TakeFive and loops until there is an error,
//          someone wins or there is a tie.
// Returns: The winner as Player enum.
//-----------------------------------------------------------------------------
Player Gomoku::_play()
{
    auto game = new TakeFive(_boardHeight, _boardWidth);
    auto moves = 0;
    auto maxMoves = _boardHeight * _boardWidth;
    auto winner = NONE;

    game->startNewGame();

    while (winner == NONE && moves++ < maxMoves)
    {
        CLEARSCREEN;
        game->show();

        if (_playerToDoNextMove)
        {
            int row;
            char column;

            _getPosition(row, column);

            winner = game->makeMove(_player, row, column);
        }
        else
        {
            cout << "Press enter to see your opponents move." << endl;
            cin.get();
            winner = game->makeMove(_computer);
        }

        _playerToDoNextMove = !_playerToDoNextMove;
    }

    CLEARSCREEN;
    game->show();

    delete game;

    return winner;
}

//-----------------------------------------------------------------------------
// void _showResult(Player winner)
//
// Summary: Displays the result of the game.
// Returns: -
//-----------------------------------------------------------------------------
void Gomoku::_showResult(Player winner)
{
    if (winner == ERROR)
    {
        cout << "Somethihng went wrong. Game is aborted." << endl;
    }
    else if ( _player == winner)
    {
        cout << "Congratulations! You won!" << endl;
    }
    else if (_computer == winner)
    {
        cout << "Sorry. You lost." << endl;
    }
    else
    {
        cout << "It's a tie." << endl;
    }

    cin.get();
}

//-----------------------------------------------------------------------------
// void _getPosition(int & row, char & column)
//
// Summary: Asks the user for the row and the column within _boardHeight and
//          _boardWidth.
// Returns: -
//-----------------------------------------------------------------------------
void Gomoku::_getPosition(int & row, char & column)
{
    auto maxColumn = 'a' + _boardWidth - 1;

    row = _getAplphaNumFromUser<int>("Please enter a row", 1, _boardHeight);
    column = _getAplphaNumFromUser<char>("Please enter a column", 'a', maxColumn);
}
