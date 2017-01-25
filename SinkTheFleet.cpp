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

		for (whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			if (whichPlayer == 0)
			{
				filename = "Player 1.txt";
				readFromFileChoice = safeChoice("Player 1, Would you like to read starting grid from a file? (Y/N):", 'Y', 'N');
				if (readFromFileChoice == 'N')
				{
					setships(game, gridSize, whichPlayer);
				}
				else if (readFromFileChoice == 'Y')
				{
					cout << "Reading from file...";
					getGrid(game, whichPlayer, gridSize, filename);
				}
			}
			else if (whichPlayer == 1)
			{
				filename = "Player 2.txt";
				readFromFileChoice = safeChoice("Player 2, Would you like to read starting grid from a file? (Y/N):", 'Y', 'N');
				if (readFromFileChoice == 'N')
				{
					setships(&game[NUMPLAYERS], gridSize, whichPlayer);
				}
				else if (readFromFileChoice == 'Y')
				{
					cout << "Reading from file...";
					getGrid(game, whichPlayer, gridSize, filename);
				}
			}
			whichPlayer++;

		}
		whichPlayer = 0;
		while (!gameOver)
		{
			// ... a lot more stuff ...


			whichPlayer = !whichPlayer;  // switch players
		}

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	} while (again == 'Y');

	return EXIT_SUCCESS;
}