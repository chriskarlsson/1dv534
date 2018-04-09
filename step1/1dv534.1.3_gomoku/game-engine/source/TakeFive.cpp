/**********************************************************************
 File:		TakeFive.cpp  -  implementation file for class TakeFive
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

#include "TakeFive.h"
#include <iostream>
	using std::cout;
	using std::endl;
#include <iomanip>
	using std::setw;

//--- constants for stepping in 4 different directions when tracing a "ship"
const int TakeFive::STEP_X[4] = { 0 , 1 ,-1 , 1 };
const int TakeFive::STEP_Y[4] = { 1,  0 , 1 , 1 };
//--- constant telling how many ships that will be gathered when computing next move
const int QUEUESIZE = 1000;


/******************************************************************************
 				TakeFive ( int rows, int cols )
 				-------------------------------
 Description:	This is the only constructor for class TakeFive. Caller has
 				to decide the size of the board before creating it. The board
 				is initialized to an empty board, ready for first move by any
 				of the players.
 
 Pre:			The caller has to determine the size of the board and pass
 				the number of rows and columns as parameters in the call.
 				Number of rows must be greater than 5 and should probably
 				be less than 75, even if no maximum value is enforced.
 				Columns are designated by a character, which means that
 				number of columns should be in range 5 - 55 (because there
 				are no more letters available).
 
 Post:			An empty board is created an initialized for play. Any player
 				may make the first move, but following move must always be
 				made by the opponent.
 				The board is created from dynamic memory, which must be released
 				by the constructor when the object is destroyed.
 				A message is written to the screen describing the created board. 

 Parameters:
	rows:		The vertical size of the board specified as number of rows.
 				Should be in range 5 - 75.
 	cols:		The horizontal size of the board specified as number of
 				columns. Should be in range 5 - 55.

******************************************************************************/

TakeFive::TakeFive(int rows, int cols)
{
	_board = new char* [rows];

	for (int i = 0; i < rows; ++i)
		_board[i] = new char[cols];

	for (int r = 0; r < rows; ++r)
		for (int c = 0; c < cols; ++c)
			_board[r][c] = ' ';
	_rows = rows;
	_cols = cols;
	_gameActive = true;
	_lastPlayer = NONE;
	cout << "The gameboard is now created with " << rows
		  << " rows and " << cols << " columns.\n" << endl;
}


/******************************************************************************
 				~TakeFive ()
 				------------
 Description:	This is the destructor for class TakeFive. It will release the
				dynamic memory allocated by the constructor.
 
 Pre:			Board will no longer be used, and should therefore be destroyed.

 Post:			Dynamic memory has been released.
				A message is written to the screen telling that the board has been
				destroyed.

 Parameters:	None

******************************************************************************/

TakeFive::~TakeFive()
{
	for (int row = 0; row < _rows; ++row)
		delete [] _board[row];
	delete [] _board;
	cout << "The gameboard is now cleared and removed." << endl;
}


/******************************************************************************
				startNewGame ( )
				----------------
 Description:	This method will reinitialize the board for a new game. The
				size of the board will remain unchanged.

 Pre:			The last game is no longer of interest and can be destroyed.

 Post:			The board is reinitialized to an empty board ready for a new game.

 Parameters:	None

******************************************************************************/

void TakeFive::startNewGame()
{
	for (int r = 0; r < _rows; ++r)
		for (int c = 0; c < _cols; ++c )
			_board[r][c] = ' ';
	_gameActive = true;
	_lastPlayer = NONE;
	cout << "The game board has now been initiated for a new game." << endl;
}


/******************************************************************************
 				makeMove ( Player player, int row, char colCh )
 								-----------------------------------------------
 Description:	The caller makes a move by calling this method. The parameters
				specify the target position. Row number is always specified as
				an integer number, but the column is identified by a character
				which is shown when the screen is printed to screen ( by a call
				to method show() )

 Pre:			It's the player's turn to make next move, and the specified
				position (row and colCh) designates an empty square on the board.				

 Post:			The player's mark is entered into the target position, and
				the board is checked for a winning ship.

 Parameters:
	player:		Identifies which player makes the move.
				Should be either CROSS or RING.
	rows:		Specifies the row coordinate of the target square.
				Should specify an empty square on the board.
	cols:		Specifies the character that represents the target column.
				Should specify an empty square on the board.

 Returns:		Method returns NONE if no winning ship has been detected yet.
				If a winning ship (size=5) has been detected, the method returns
				the ID of the winner (CROSS or RING).
				If the call fails, the method will return ERROR.

******************************************************************************/

Player TakeFive::makeMove(Player player, int row, char colCh)
{
	int col = (colCh >= 'a' ? colCh-97 : colCh-65);
	--row;

	if (player == _lastPlayer || !_gameActive ||
		  row < 0 || row >= _rows ||
		  col < 0 || col >= _cols ||
		  _board[row][col] != ' ')
		return ERROR;
	char ch;

	switch (player) {
		case  CROSS :
			ch = 'X';
			break;
		case  RING :
			ch = 'O';
			break;
		default:
			ch = '?';
			break;
	}
	_board[row][col] = ch;
	return _lookForWinner();
}


/******************************************************************************
				makeMove ( Player player )
				--------------------------
 Description:	The caller requests the object itself to perform the next move.
				The parameter shows for which player the move is made.

 Pre:			It's the player's turn to make next move.

 Post:			The player's mark is entered into the selected position, and
				the board is checked for a winning ship.

 Parameters:
	player:		Identifies which player makes the move.
				Should be either CROSS or RING.

 Returns:		Method returns NONE if no winning ship has been detected yet.
				If a winning ship (size=5) has been detected, the method 
				returns the ID of the winner (CROSS or RING).
				If the call fails, the method will return ERROR.

******************************************************************************/

Player TakeFive::makeMove(Player player)
{
	Ship myQ[QUEUESIZE], oppQ[QUEUESIZE];	// here we create queues for all ships found on board
	int myQix = 0, oppQix = 0;	// indexes telling how many entries each queue contains
	char myCh = (player == CROSS ? 'X' : player == RING ? 'O' : '?');
	char oppCh = (player == CROSS ? 'O' : player == RING ? 'X' : '?');

	if ((player != CROSS && player != RING) || player ==_lastPlayer || !_gameActive)
		return ERROR;
	_gatherShips(player, myQ, myQix, oppQ, oppQix, _board);

	//--- Playing Strategy
	//--- ================
	int row, col;				// will be updated to contain move to be made
	bool moveFound = false;	// will be set to true when row and col contains a move

	//--- case 1: Board is almost empty
	if (myQix == 0 && oppQix == 0) {

		for (int r = 0; r < _rows; ++r)
			for (int c = 0; c < _cols; ++c)
				if (_board[r][c] != ' ') {

					if (_legalMove(r-1, c-1)) {
						_board[r-1][c-1] = myCh;
						return _lookForWinner();
					}
					if (_legalMove(r-1, c+1)) {
						_board[r-1][c+1] = myCh;
						return _lookForWinner();
					}
					if (_legalMove(r-1, c)) {
						_board[r-1][c] = myCh;
						return _lookForWinner();
					}
					if (_legalMove(r, c-1)) {
						_board[r][c-1] = myCh;
						return _lookForWinner();
					}
					if (_legalMove(r, c+1)) {
						_board[r][c+1] = myCh;
						return _lookForWinner();
					}
				}
				if (_legalMove(_rows/2,_cols/2)) {
					_board[_rows/2][_cols/2] = myCh;
					return _lookForWinner();
				}
				return ERROR;
	}

	//--- case 2: I have an unblocked 4-ship and can make the winning move
	if (myQ[0].size == 4) {
		row = myQ[0].y - STEP_Y[myQ[0].dir];
		col = myQ[0].x - STEP_X[myQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		row = myQ[0].y + myQ[0].size * STEP_Y[myQ[0].dir];
		col = myQ[0].x + myQ[0].size * STEP_X[myQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		return ERROR;
	}

	//--- case 3: Opponent has an unblocked 3-ship that must be blocked
	if (oppQ[0].size == 4 || (oppQ[0].size >= 3 && oppQ[0].openEnds == 2)) {
		row = oppQ[0].y - STEP_Y[oppQ[0].dir];
		col = oppQ[0].x - STEP_X[oppQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		row = oppQ[0].y + oppQ[0].size * STEP_Y[oppQ[0].dir];
		col = oppQ[0].x + oppQ[0].size * STEP_X[oppQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		return ERROR;
	}

	//--- case 4: I have entries in my queue
	if (myQix > 0) {
		row = myQ[0].y - STEP_Y[myQ[0].dir];
		col = myQ[0].x - STEP_X[myQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		row = myQ[0].y + myQ[0].size * STEP_Y[myQ[0].dir];
		col = myQ[0].x + myQ[0].size * STEP_X[myQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		return ERROR;
	}

	//--- case 5: Opponent has entries in his/her queue
	if (oppQix > 0) {
		row = oppQ[0].y - STEP_Y[oppQ[0].dir];
		col = oppQ[0].x - STEP_X[oppQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		row = oppQ[0].y + oppQ[0].size * STEP_Y[oppQ[0].dir];
		col = oppQ[0].x + oppQ[0].size * STEP_X[oppQ[0].dir];

		if (_legalMove(row, col)) {
			_board[row][col] = myCh;
			return _lookForWinner();
		}
		return ERROR;
	}
	return ERROR;	// makes the compiler satisfied  ;-)
}


/******************************************************************************
				show ()
				-------
 Description:	The state of the board is written to the console window.

 Pre:			None

 Post:			Console window shows the board state.

 Parameters:	None

******************************************************************************/

void TakeFive::show() const
{
	cout <<"   ";

	for (int col = 0; col < _cols; ++col) 
		cout << char(col < 26 ? 65+col : 71+col) << ' ';
	cout << endl;
	cout << "  " << char(218);

	for (int col = 1; col < _cols; ++col) 
		cout << char(196) << char(194);
	cout << char(196) << char(191);
	cout << endl;

	for (int row = 0; row < _rows; ++row) {
		cout << setw(2) << row+1;

		for (int col = 0; col < _cols; ++col)
			cout << char(179) << _board[row][col];
		cout << char(179) << endl;
	}
	cout <<"  " << char(192);

	for (int col = 1; col < _cols; ++col) 
		cout << char(196) << char(193);
	cout << char(196) << char(217);
	cout << endl;
}


/******************************************************************************
 (internal)		_lookForWinner ()
				-----------------
 Description:	The board is searched for a ship containing 5 or more squares.
				If one is found, the corresponding player ID is returned. If
				no winning ship is found, NONE is returned.

 Pre:			None

 Post:			The returned value shows if someone has won the game.

 Parameters:	None

 Returns:		NONE	= No winner has been found yet
				CROSS	= A ship of crosses has been found with 5 or more squares
				RING	= A ship of rings has been found with 5 or more squares
				ERROR	= The state of the board is bad

******************************************************************************/

Player TakeFive::_lookForWinner() const
{
	bool winningShip = false;
	Ship ship;

	for (int row = 0; row < _rows; ++row)
		for (int col = 0; col < _cols; ++col)
			if (_board[row][col] == 'X' || _board[row][col] == 'O')
				for (int dir = 0; dir < 4; ++dir) {
					ship = _createShip(row, col, dir, _board);

					if (ship.size >= 5)
						return ship.player;
				}
	return NONE;
}


/******************************************************************************
 (internal)		_createShip ( int row, char col, int direction )
				------------------------------------------------
 Description:	The caller requests the object itself to perform the next move.
				The parameter shows for which player the move is made.

 Pre:			It's the player's turn to make next move.

 Post:			The player's mark is entered into the selected position, and
				the board is checked for a winning ship.

 Parameters:
	player:		Identifies which player makes the move.
				Should be either CROSS or RING.

 Returns:		Method returns NONE if no winning ship has been detected yet.
				If a winning ship (size=5) has been detected, the method returns
				the ID of the winner (CROSS or RING).
				If the call fails, the method will return ERROR.

******************************************************************************/

TakeFive::Ship	TakeFive::_createShip(int row, int col, int direction, char** board) const
{
	int  stepX = STEP_X[direction];
	int  stepY = STEP_Y[direction];
	Ship ship;
	//--- create an empty ship to return at failure
	ship.valid	= false;
	ship.player	= board[row][col] == 'X' ? CROSS : board[row][col] == 'O' ? RING : ERROR;
	ship.dir	= direction;
	ship.size	= 0;
	ship.openEnds = 0;
	ship.x		= col;
	ship.y		= row;
	//--- detect failure situations and return the empty ship when they occur
	char ownCh = board[row][col];

	if (ownCh != 'X' && ownCh != 'O')	// createShip should be called only for squares containing "X" or "O"
		return ship;
	char opponentCh = (ownCh == 'X' ? 'O' : 'X');
	char endCh;
	int y = row - stepY;
	int x = col - stepX;

	if (x >= 0 && x < _cols && y >= 0 && y < _rows)
		endCh = board[y][x];
	else
		endCh = opponentCh;

	//--- if location is contained within a ship just return the empty ship
	if (endCh == ' ')	// if open end, increase openEnds
		++ship.openEnds;
	else if (endCh != opponentCh)
		return ship;
	//--- step through ship and compute its size
	ship.valid = true;

	while (board[row][col] == ownCh){
		++ship.size;
		row += stepY;
		col += stepX;

		if (row < 0 || row >= _rows || col < 0 || col >= _cols)
			  return ship;
	}
	if (board[row][col] == ' ')
		++ship.openEnds;
	return ship;
}


/******************************************************************************************
 (internal)		_insertShip ( const Ship& ship, Ship queue[], int& index )
				----------------------------------------------------------
 Description:	The ship in 1'st parameter will be inserted into the queue
				specified by 2'nd parameter in sorted order. The 3'rd parameter
				is a counter telling how many entries are already in queue.
				Index will be updated by the call (increased by one).

 Pre:			The queue may be full but index must always tell exactly
				how many entries are in queue. The queue must be filled from
				the head, making all free space located after all entries.
				If the queue is full, the last element will be discarded.

 Post:			A copy of the ship specified in first parameter has been inserted
				into the queue in sorted order on size(1) and openEnds(2), with a
				high value stored before a lower one.

 Parameters:
	ship:		Ship to be inserted inte the queue. The ship must support operator =
				for creating a copy of the original.
				Should be a valid ship belonging to either player CROSS or RING.
	queue:		Specifies a queue where there may or may not be room for more entries.
				If queue is full, last element is discarded.
				Should be a vector containing ships in queue[0]..queue[index-1].
	index:		An integer showing how many entries there are in the queue.
				Should be an integer varaible that shows number of ships in queue

 Returns:		Nothing

******************************************************************************************/

void TakeFive::_insertShip(const Ship& ship, Ship queue[], int& index) const
{
	int i;

	if (index == 0)
		queue[index] = ship;
	else {
		i = (index == QUEUESIZE ? index-1 : index);

		while (i > 0 &&  
			    (queue[i-1].size < ship.size ||
				 (queue[i-1].size == ship.size && queue[i-1].openEnds < ship.openEnds))) {
			queue[i] = queue[i-1];
			--i;
		}
		queue[i] = ship;
	}
	++index;
}


/************************************************************************************************************
  (internal)	_gatherShips ( Player player, Ship myQ[], int& myQix, Ship oppQ[], int& oppQix, const char** board )
				----------------------------------------------------------
 Description:	Ships with 2 or more squares are gathered together in the two queues myQ and oppQ.
				The ships belonging to player will be inserted in myQ and the opponent's ships will
				be inserted in oppQ. Parameters myQix and oppQix are counters that tell how many
				ships that the respective queues contain.

 Pre:			The queues may contain ships from the start or be totally empty. If there are any ships
				in the que, they will be discarded and myQix and oppQix will be cleared at the beginning.

 Post:			Ships with open ends consisting of more than 1 square will be entered into the queue myQ
				if it belongs to the player specified in parameter 1, and into oppQ if the ship belongs
				to player's opponent. myQix and oppQix will be updated to reflect the number of ships
				that has been stored in the queues.

 Parameters:
	player:		Specifies which player will get his/her ships in the myQ queue
				Should contain either CROSS or RING.
	myQ:		Specifies the queue that will be filled with ships belonging to player
				Should be an empty vector that will hold sufficiently many ships.
	oppQ:		Specifies the queue that will be filled with ships belonging to opponent to player
				Should be a vector that will hold sufficiently many ships.
	oppQix:		An integer showing how many entries there are in the oppQ queue.
				Should be an integer varaible that shows first free index in queue
	board:		A matrix containing the contents of the board in character format

 Returns:		Nothing

************************************************************************************************************/

void TakeFive::_gatherShips(Player player, Ship myQ[], int& myQix, Ship oppQ[], int& oppQix, char** board) const
{
	Ship ship;							// used to temporary store result from call to _createShip

	for (int row = 0; row < _rows; ++row)
		for (int col = 0; col < _cols; ++col)
			if (board[row][col] == 'X' || board[row][col] == 'O')
				for (int dir = 0; dir < 4; ++dir) {
					ship = _createShip(row, col, dir, board);

					if (ship.valid &&			// if this ship is important
						  ship.openEnds > 0 && ship.size > 1) {	// ... insert ship in corresponding queue

						if (ship.player == player)
							_insertShip(ship, myQ, myQix);
						else
							_insertShip(ship, oppQ, oppQix);
					}
				}

//********************* This block is only for debugging purposes *******************************

				cout << "Contents of myQ for player " << player << endl;
				for (int i = 0; i < myQix; ++i)
					cout << (myQ[i].player == CROSS ? 'X' : myQ[i].player == RING ? 'O' : '?') <<
								myQ[i].size << myQ[i].openEnds << '(' << myQ[i].y+1 << ',' << myQ[i].x+1 << ')' << ' ';
				cout << "\nContents of oppQ for player " << player << endl;
				for (int i = 0; i < oppQix; ++i)
					cout << (oppQ[i].player == CROSS ? 'X' : oppQ[i].player == RING ? 'O' : '?') <<
								oppQ[i].size << oppQ[i].openEnds << '(' << oppQ[i].y+1 << ',' << oppQ[i].x+1 << ')' << ' ';
				cout << endl;

//**********************************************************************************************/

}

