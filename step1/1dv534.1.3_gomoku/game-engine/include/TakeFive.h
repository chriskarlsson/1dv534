/**********************************************************************
 File:		TakeFive.h  -  header file for class TakeFive
 Summary:	Class TakeFive produces objects that play "Naughts and Crosses"
			(Swedish "Luffarschack"). The caller determines whether or not
			the object itself determines the target position for the move
			or if the caller supplies row and column coordinates.
			The only rule enforced by the object is that even if any player
			may start a game, no player may make two or more moves in a row.
			When game is over, the object may be reused for next play, or
			replaced by a new object. Both ways are possible. Use method
			startNewGame() if you want to reset the object for next game.

 Version:	1.0 - 2005-08-23, Copyright Högskolan i Kalmar
 Author:	Christer Lundberg, Institutionen för Teknik, Högskolan i Kalmar.
 --------------------------------------------------------------------
 Log:		2013-03-28	Uppdate  Version 1.1 by Anne. 
					Converted to VS 2012
			2015-03-05	Revised by Anne. Converted to VS 2013
**********************************************************************/

#ifndef TAKEFIVE
#define TAKEFIVE


enum Player { NONE, ERROR, CROSS, RING };					// identifier for players

class TakeFive {
public:
	TakeFive( int rows, int cols );							// gives board size and object's symbol
	~TakeFive();											// destructor is needed to free allocated board memory
	Player makeMove( Player player, int row, char col );	// caller wants a move performed
	Player makeMove( Player player );						// the object itself is supposed to make the move
	void startNewGame();									// reset object to start a new game using crosses if parm true
	void show() const;										// show the board in console window on screen
	bool gameIsActive() const { return _gameActive; }		// shows that a game has been started and is running
private:
	int    _rows, _cols;		// shows the size of the board
	bool   _gameActive;			// shows that an active game is going on
	char** _board;				// shows the current state of the board
	Player _lastPlayer;			// shows which player performed the last move
	//--- local structs can be declared within another class
	struct Ship {
		bool		valid;		// shows wether or not this ship is a valid one
		Player		player;		// CROSS or RING to tell which player
		int			dir;		// direction of ship
		int			size;		// shows how many characters there are in the ship
		int			openEnds;	// shows how many ends of the ship that are open ( 0, 1 or 2 )
		int			x, y;		// position of topmost (dir!=RIGHT) or leftmost (dir==RIGHT) position in ship
	};
	//--- constants for various directions
	static const int STEP_X[4];
	static const int STEP_Y[4];
	//--- internal help routines
	Player _lookForWinner() const;
	Ship   _createShip( int row, int col, int dir, char** board ) const;
	void   _gatherShips(Player player, Ship myQ[], int& myQix, Ship oppQ[], int& oppQix, char** board ) const;	
	void   _insertShip( const Ship& ship, Ship queue[], int& index ) const;
	bool   _legalMove( int row, int col ) const	{	// determines if the location is an empty square on the board
		return  row >= 0 && row < _rows &&
				col >= 0 && col < _cols &&
				_board[row][col] == ' ';
	}
};

#endif
