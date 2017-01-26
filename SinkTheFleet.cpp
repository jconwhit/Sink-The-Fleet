//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "fleet.h"
using namespace std;
extern const char* shipNames[7];
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
// modified by:
// 
// Date:		12/9/2010
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2013
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				getGrid()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2010 PB completed v 0.5
//   
//---------------------------------------------------------------------------------
int main(void)
{
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char gridSize = 'S';
	char readFromFileChoice = 'N';
	short whichPlayer = 0;
	short otherPlayer = 1;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = { 0, 0 };
	string message;
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS];	// the two players in an array
								// other stuff ...

	do
	{
		system("cls");
		cout << endl;
		header(cout);
		for (whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			if (whichPlayer == 0)
			{
				filename = "Player 1.txt";
				system("cls");
				header(cout);
				readFromFileChoice = safeChoice("Player 1, Would you like to read starting grid from a file?", 'Y', 'N');
				if (readFromFileChoice == 'N')
				{
					gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');

					if (gridSize == 'L')
					{
						numRows = LARGEROWS;
						numCols = LARGECOLS;
					}
					else
					{
						numRows = SMALLROWS;
						numCols = SMALLCOLS;
					}
					initializePlayer(game);
					initializePlayer(game + 1);

					// dynamically create the rows of the array
					allocMem(game, gridSize);
					setships(game, gridSize, whichPlayer);
				}
				else if (readFromFileChoice == 'Y')
				{
					cout << "Reading from file...";
					getGrid(game, whichPlayer, gridSize, filename);
					printGrid(cout, game[whichPlayer].m_gameGrid[0], gridSize);
					cout << "Press <enter> to continue.." << endl;
					cin.get();
				}
			}
			else if (whichPlayer == 1)
			{
				filename = "Player 2.txt";
				system("cls");
				header(cout);
				readFromFileChoice = safeChoice("Player 2, Would you like to read starting grid from a file?", 'Y', 'N');
				if (readFromFileChoice == 'N')
				{
					gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');

					if (gridSize == 'L')
					{
						numRows = LARGEROWS;
						numCols = LARGECOLS;
					}
					else
					{
						numRows = SMALLROWS;
						numCols = SMALLCOLS;
					}
					setships(game, gridSize, whichPlayer);
				}
				else if (readFromFileChoice == 'Y')
				{
					cout << "Reading from file...";
					getGrid(game, whichPlayer, gridSize, filename);
					printGrid(cout, game[whichPlayer].m_gameGrid[0], gridSize);
					cout << "Press <enter> to continue.." << endl;
					cin.get();
				}
			}

		}
		whichPlayer = 0;

		//start of battle
		system("cls");
		header(cout);
		cout << "Player " << whichPlayer + 1 << ", press <enter> to start the battle..." << endl;
		cin.get();

		while (gameOver == false)
		{

			system("cls");
			if (whichPlayer == 0)
				otherPlayer = 1;
			else
				otherPlayer = 0;
			shipHit = NOSHIP;
			cout << endl;
			header(cout);
			printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
			cout << "Player " << whichPlayer + 1 << ", enter coordinates for firing." << endl;
			coord = getCoord(cin, gridSize);
			if (game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] == (MINESWEEPER) ||
				game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] == (SUB) ||
				game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] == (FRIGATE) ||
				game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] == (BATTLESHIP) ||
				game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] == (CARRIER))
			{
				//keeps track of what ship was hit
				shipHit = game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col];

				game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] = HIT;

				game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;
				printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
				cout << "HIT!" << endl;
				game[otherPlayer].m_piecesLeft -= 1;
				cout << "Player " << (otherPlayer + 1) <<
					" has " << game[otherPlayer].m_piecesLeft <<
					" pieces left." << endl;
				cout << "Press <enter> to fire again." << endl;
				if (game[otherPlayer].m_piecesLeft == 0)
				{
					gameOver = true;
					system("cls");
					header(cout);
					cout << "CONGRADULATIONS PLAYER " << whichPlayer + 1 <<
						", YOU WON WITH " << game[whichPlayer].m_piecesLeft <<
						" PIECES REMAINING!" << endl;
					cout << "Press <enter> to continue.." << endl;
				}
				cin.get();
			}
			else if (game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] == (HIT))
			{
				system("cls");
				printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
				cout << "You have already shot at" << 
					(static_cast<char>(coord.m_row + 'A')) << 
					(coord.m_col + 1) << ". Press <enter> to fire again." << endl;
				cin.get();
			}
			else
			{
				/*Marks the current player's hit/miss grid to indicate
				where they have previously missed*/
				game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = MISSED;

				/*Marks the position to indicate that the current 
				player has already fired at this position. Does NOT subtract
				pieces from the opponent.*/
				game[otherPlayer].m_gameGrid[0][coord.m_row][coord.m_col] = HIT; 

				cout << "MISS!" << endl;
				cout << "Player " << (otherPlayer + 1) <<
					" still has " << game[otherPlayer].m_piecesLeft <<
					" pieces left." << endl;
				cout << "Press <enter> to end your turn." << endl;
				whichPlayer = otherPlayer; //changes player when a shot misses
				cin.get();
			}
			

		}

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	} while (again == 'Y');

	return EXIT_SUCCESS;
}
//
