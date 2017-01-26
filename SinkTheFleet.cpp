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

		// ... your code goes here

		for (whichPlayer = 0; whichPlayer <= NUMPLAYERS; whichPlayer++)
		{
			if (whichPlayer == 0)
			{
				filename = "Player 1.txt";
				readFromFileChoice = safeChoice("Player 1, Would you like to read starting grid from a file?", 'Y', 'N');
				if (readFromFileChoice == 'N')
				{
					setships(game, gridSize, whichPlayer);
				}
				else if (readFromFileChoice == 'Y')
				{
					cout << "Reading from file...";
					getGrid(game, whichPlayer, gridSize, filename);
					printGrid(cout, game[whichPlayer].m_gameGrid[0], gridSize);
				}
			}
			else if (whichPlayer == 1)
			{
				filename = "Player 2.txt";
				readFromFileChoice = safeChoice("Player 2, Would you like to read starting grid from a file?", 'Y', 'N');
				if (readFromFileChoice == 'N')
				{
					setships(game, gridSize, whichPlayer);
				}
				else if (readFromFileChoice == 'Y')
				{
					cout << "Reading from file...";
					getGrid(game, whichPlayer, gridSize, filename);
					printGrid(cout, game[whichPlayer].m_gameGrid[0], gridSize);
				}
			}
			//whichPlayer++;

		}
		whichPlayer = 0;
		while (!gameOver)
		{
			system("cls");
			cout << endl;
			header(cout);
			cout << "Press <enter> to start the battle..." << endl;
			while (whichPlayer == 0)
			{
				system("cls");
				printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
				cout << "Player " << whichPlayer + 1 << ", Enter Coordinates for Firing." << endl;
				coord = getCoord(cin, gridSize);
				if (game[whichPlayer + 1].m_gameGrid[0][coord.m_row][coord.m_col] != NOSHIP)
				{
					//struct ShipInfo
					//{
					//	Ship m_name;			// which ship?
					//	Direction m_orientation;// which direction is the ship facing? 
					//	Cell m_bowLocation;		// which cell is the bow location?
					//	short m_piecesLeft;		// how many sections are left undestroyed?
					//};
					game[whichPlayer + 1].m_gameGrid[0][coord.m_row][coord.m_col] = shipHit;
					//ShipInfo[].m_piecesLeft;
					game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					cout << "HIT" << endl;

				}
				else
				{
					game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = MISSED;
					cout << "MISS" << endl;
					whichPlayer++;
				}
			}
			while (whichPlayer == 1)
			{
				system("cls");
				printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
				cout << "Player " << whichPlayer + 1 << ", Enter Coordinates for Firing." << endl;
				coord = getCoord(cin, gridSize);
				if (game[whichPlayer - 1].m_gameGrid[0][coord.m_row][coord.m_col] != NOSHIP)
				{
					game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					cout << "HIT" << endl;
				}
				else
				{
					game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = MISSED;
					cout << "MISS" << endl;
					whichPlayer++;
				}
			}
			whichPlayer = !whichPlayer;  // switch players
		}

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	} while (again == 'Y');

	return EXIT_SUCCESS;
}
//
