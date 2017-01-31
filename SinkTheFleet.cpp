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
	short numCols = SMALLCOLS;
	char again = 'N';
	char gridSize = 'S';
	char readFromFileChoice = 'N';
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = { 0, 0 };
	string filename;
	Ship shipHit = NOSHIP;
	ShipInfo targetInfo;
	Player game[NUMPLAYERS];	// the two players in an array
								// other stuff ...
	

	do
	{
		system("cls");
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


		for (whichPlayer = 0; whichPlayer <= NUMPLAYERS; whichPlayer++)
		{
			if (whichPlayer == 0)
			{
				filename = "Player 1.txt";
				system("cls");
				header(cout);
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
		system("cls");
		header(cout);
		cout << "Press <enter> to start the battle..." << endl;
		cin.ignore(BUFFER_SIZE, '\n');

		whichPlayer = 0;
		gameOver = false;
		while (!gameOver)
		{
			do
			{

				printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
				reshot = false;
				cout << "Player " << whichPlayer + 1 << ", Enter Coordinates for Firing." << endl;

				coord = getCoord(cin, gridSize);

				shipHit = game[!whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col];


				//If the space is not empty
				if (shipHit != NOSHIP)
				{
					system("cls");
					//if space has already been hit
					if (shipHit == HIT)
					{
						printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
						cout << "THIS SPACE HAS PREVIOUSLY BEEN HIT." << endl;
					}
					//without this the program will detect re-firing at a missed cell as a hit
					else if (shipHit == MISSED) 
					{
						printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
						cout << "THIS SPACE HAS PREVIOUSLY BEEN MISSED." << endl;
					}
					else
					{
						//decrease total enemy fleet
						game[!whichPlayer].m_piecesLeft--;
						//decrease pieces of ship left	
						targetInfo = game[!whichPlayer].m_ships[shipHit];
						targetInfo.m_piecesLeft--;
						game[!whichPlayer].m_ships[shipHit].m_piecesLeft--;

						//adjust grid for hit
						game[!whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col] = HIT;
						game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;
						printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
						cout << "HIT" << endl;

						if (targetInfo.m_piecesLeft == 0)
						{
							cout << shipNames[targetInfo.m_name] << " is destroyed." << endl;
						}
						if (game[!whichPlayer].m_piecesLeft == 0)
						{
							gameOver = true;
							cout << "Enemy fleet has been destroyed." << endl;
							cin.ignore(BUFFER_SIZE, '\n');
							system("cls");
							break;
						}
					}
					reshot = true;

				}
				else
				{
					//adjust for miss
					game[!whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col] = MISSED;
					game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = MISSED;
					printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
					cout << "MISS" << endl;
				}

				cout << "Press <enter> to contine." << endl;
				cin.ignore(BUFFER_SIZE, '\n');
				system("cls");
			} while (reshot);

			if (gameOver)
				break;
			whichPlayer = !whichPlayer;  // switch players
		}

		//show ending dialouge w/ winner
		endBox(whichPlayer);

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	} while (again == 'Y');
	//where deletemem will go
	deleteMem(game, gridSize);

	return EXIT_SUCCESS;
}