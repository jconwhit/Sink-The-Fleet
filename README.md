# Sink-The-Fleet
Project 1 - Winter 2017 EdmondsCC


2017-01-14 - JW Realized we were just printing the grid 
  to the output stream when we need to be implementing the 
  array (that was previously allocated) to store ship output 
  information for our print function.

this is the function for getgrid. I did not want to overwrite the master since I could not get the saveGrid function to work.


bool getGrid(Player players[], short whichPlayer, char size, string fileName)
{
	string line;
	ifstream ifs;
	Ship ship = NOSHIP;
	char fsize = 'S';
	char input = NULL;
	char row = 'A';
	int col = 0;
	char save = 'N';
	Ship ship_type;
	Cell location = { 0, 0 };
	//short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	//short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		ifs.open(fileName.c_str());
		if (!ifs)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			return false;
		}
	}
	catch (exception e)
	{
		cout << "could not open file " << fileName << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return false;
	}

	fsize = toupper(ifs.get());
	ifs.ignore(FILENAME_MAX, '\n');
	short numberOfRows = (toupper(fsize) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(fsize) == 'L') ? LARGECOLS : SMALLCOLS;

	for (short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
	{
		input = toupper(ifs.get());
		players[whichPlayer].m_ships[j].m_orientation
			= (input == 'V') ? VERTICAL : HORIZONTAL;
		getline(ifs, line);
		row = toupper(line.at(1));
		col = line.at(2);
		location.m_col = col - 49;
		location.m_row = static_cast<short>(row - 'A');
		players[whichPlayer].m_ships[j].m_bowLocation = location;

		ship_type = static_cast<Ship>(j);
		players[whichPlayer].m_gameGrid[0][location.m_row][location.m_col] = ship_type;

		for (int i = 0; i < shipSize[j]; i++)
		{
			if (input == 'V')
			{
				players[whichPlayer].m_gameGrid[0][location.m_row + i][location.m_col] = ship_type;
			}
			else
			{
				players[whichPlayer].m_gameGrid[0][location.m_row][location.m_col + i] = ship_type;
			}
		}

	} // end for j
	printGrid(cout, players[whichPlayer].m_gameGrid[0], fsize);
	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if (save == 'Y')
		saveGrid(players, whichPlayer, fsize);
	return true;
}
