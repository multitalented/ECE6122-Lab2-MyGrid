/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 9/28/2020

Description:

This is the .cpp file defining MyGrid class
myX myY
nRows nCols
[] [] []----numCols
[] .
.	 .
.		

numRows	  []

myX, myY refer to the location of the MyGrid object in a global coordinate system such that

Y_global   			___________>x
^					|myGrid|
|					|______|
|					|
|					y
|
|
|____________________________________> X_global

The program uses a MyGrid class that stores the information from the input files into
objects that are defined by a matrix of values called gridElements
and their corresponding numbers of rows and columns, and the global location
of the matrix in a global coordinate system

The program then performs operations with these MyGrid objects using the
operator overloaded functions and outputs the results to an output file
*/

#include "MyGrid.h"

////////////////////////////////////////////////////////////////////
// FUNCTION: LOAD A MYGRID OBJECT FROM INPUT TEXT FILE
//	INPUT:	STRING
//	RETURN: BOOL
//****************************************************************
// The MyGrid object being operated on with this function will
//		be updated to having the values taken from the text file
bool MyGrid::loadGridFromFile(const string& filename)
{
	long num = 0;						// variable to store each number input from txt file
	ifstream thisFile(filename);		// ifstream object of input file to get data stream from
	bool gotData = false;				// whether data has been retrieved and stored into vector
	vector<long> gridData;				// create a single vector of numbers from the stream of input in txt file

	if (thisFile.is_open())				// opens file if not already open
	{
		while (thisFile >> num)			// while taking in numbers from input file to num, delimited by space by default...
		{
			gridData.push_back(num);	// add the new num to the vector gridData numbers
		}
		thisFile.close();				// close the file
		gotData = true;					// data has been retrieved
	}
	if (gotData = true)
	{
		this->myX = gridData[0];		// first value is myX
		this->myY = gridData[1];		// second value is myY
		this->m_numRows = gridData[2];	// third value is the number of rows
		this->m_numCols = gridData[3];	// fourth value is the number of columns
		unsigned long k = 4;						// the 4th value will always be the start of the actual data in grid

		vector<long> gridRow(this->m_numCols, 0);		// create a vector row of zeros of size determined by number of columns
		vector<vector<long>> gridNums(this->m_numRows, gridRow);					// create a vector to input data called gridNums
		/*
		for (long n = 0; n < this->m_numRows; ++n)		// for the number of rows...
		{
		gridNums.push_back(gridRow);				// add a vector row of zeroes to the vector of gridNums
		}
		*/
		// j = gridData.size() % k

		// i = gridData.size / k
		// j = k % i

		while (k < gridData.size())						// from k = 4 to the remainder of the gridData, fill in the matrix
		{
			for (long i = 0; i < m_numRows; ++i)		// from 0 to number of rows
			{
				for (long j = 0; j < m_numCols; ++j)	// from 0 to the number of columns
				{
					gridNums[i][j] = gridData[k];		// properly fill in the gridNums matrix from the gridData vector stream
					++k;								// add 1 to k counter
				}
			}
		}
		this->gridElements = gridNums;					// return the final matrix to this object's gridElements
	}
	else
	{
		return false;									// invalid file
	}

	return true;										// if all above runs, return true for grid having loaded
}

////////////////////////////////////////////////////////////////////
// FUNCTION: ZERO OUT GRID ELEMENTS IN MYGRID OBJECT
//	INPUT: NONE
//  OUTPUT: NONE
//****************************************************************
// The MyGrid object operated on will have its gridElements matrix
//		updated to being all zeroes
void MyGrid::zeroOutGrid()
{
	this->gridElements.clear();						// clear all elements in the operated object's gridElements vector
	vector<long> vecRow(this->m_numCols, 0);		// create a vecRow vector of zeros that is the length of the number of columns

	for (long i = 0; i < this->m_numRows; ++i)		// from 0 to the number of rows...
	{
		this->gridElements.push_back(vecRow);		// add the vecRow of zeroes for each row
	}
}
////////////////////////////////////////////////////////////////////
// FUNCTION: GET NUMBER OF ROWS OF MYGRID OBJECT
//****************************************************************
// returns private variable m_numRows
long MyGrid::getNumRows() const
{
	return this->m_numRows;			// return this object's number of rows stored in private variable m_numRows
}
////////////////////////////////////////////////////////////////////
// FUNCTION: GET NUMBER OF COLUMNS OF MYGRID OBJECT
//****************************************************************
//	returns private variable m_numCols
long MyGrid::getNumCols() const
{
	return this->m_numCols;			// return this object's number of columns stored in private variable m_numCols
}


////////////////////////////////////////////////////////////////////
// ADDITION OPERATOR WTIH MYGRID OBJECT		newGrid = gridA + gridB
//****************************************************************
// Add input Grid B to operated-on Grid A
// In this function, we define gridA as the MyGrid object being operated on
// and gridB as the MyGrid object being taken in
MyGrid MyGrid::operator+(MyGrid const& gridB) const
{
	MyGrid newGrid;
	MyGrid gridA(*this);

	// revise code, ask professor
	if (gridA.gridElements.size() == 0)		// check for condition if operated MyGrid object is an empty matrix
	{
		return gridB;				// in which case, return the grid being added
	}
	if (gridB.gridElements.size() == 0)		// check for condition if input MyGrid object is an empty matrix
	{
		return gridA;				// in which case, return the original grid
	}

	// refer to attached Excel file and scratch work for full explanation of logic
	if (gridB.myX < gridA.myX)
	{
		newGrid.myX = gridB.myX;
	}
	else
	{
		newGrid.myX = gridA.myX;
	}

	if (gridB.myY > gridA.myY)
	{
		newGrid.myY = gridB.myY;
	}
	else
	{
		newGrid.myY = gridA.myY;
	}

	newGrid.m_numRows = newGrid.myY - gridA.myY + gridA.m_numRows;
	newGrid.m_numCols = gridB.myX + gridB.m_numCols - newGrid.myX;

	newGrid.zeroOutGrid();

	long startColumnA = newGrid.myX - gridA.myX;	// relative location myX of grid A in the new master grid (start location of columns)
	long startRowA = newGrid.myY - gridA.myY;		// relative location myY of grid A in the new master grid (start location of rows)
	long startColumnB = gridB.myX - newGrid.myX;	// relative location myX of grid B in the new master grid (start location of columns)
	long startRowB = gridB.myY - newGrid.myY;		// relative location myY of grid B in the new master grid (start location of rows)

	long endColumnA = startColumnA + gridA.m_numCols - 1;	// relative end location of grid A's columns in the new master grid
	long endRowA = startRowA + gridA.m_numRows - 1;			// relative end location of grid A's rows in the new master grid
	long endColumnB = startColumnB + gridB.m_numCols - 1;	// relative end location of grid A's columns in the new master grid
	long endRowB = startRowB + gridB.m_numRows - 1;			// relative end location of grid A's rows in the new master grid

	bool Aactive = false;	// this will determine whether gridA has an element in the newGrid at a certain location (newGrid.gridElements[i][j])
	bool Bactive = false;	// this will determine whether gridB has an element in the newGrid at a certain location
	bool ABactive = false;	// this will determine whether gridA AND gridB have an element in the newGrid at a certain location

	for (long iRow = 0; iRow < newGrid.m_numRows; ++iRow)
	{
		for (long jCol = 0; jCol < newGrid.m_numCols; ++jCol)
		{
			Aactive = (iRow >= startRowA && jCol >= startColumnA && iRow <= endRowA && jCol <= endColumnA);
			Bactive = (iRow >= startRowB && jCol >= startColumnB && iRow <= endRowB && jCol <= endColumnB);
			ABactive = Aactive && Bactive;
			if (ABactive)
			{
				newGrid.gridElements[iRow][jCol] = gridA.gridElements[iRow - startRowA][jCol - startColumnA] + gridB.gridElements[iRow - startRowB][jCol - startColumnB];
			}
			else if (Aactive)
			{
				newGrid.gridElements[iRow][jCol] = gridA.gridElements[iRow - startRowA][jCol - startColumnA];
			}
			else if (Bactive)
			{
				newGrid.gridElements[iRow][jCol] = gridB.gridElements[iRow - startRowB][jCol - startColumnB];
			}
			else
			{
				newGrid.gridElements[iRow][jCol] = 0;
			}
		}
	}

	//newGrid.gridElements
	return newGrid;
}

////////////////////////////////////////////////////////////////////
// NEGATION OPERATOR WITH MYGRID OBJECT		newGrid = gridA - gridB
//****************************************************************
// Subtract input Grid B from Grid A
// In this function, we define gridA as the MyGrid object being operated on
// and gridB as the MyGrid object being taken in
/////////////////////////////////////////////////////////////////
MyGrid MyGrid::operator-(MyGrid const& gridB) const
{
	MyGrid newGrid;
	MyGrid gridA(*this);

	// revise code, ask professor
	if (gridA.gridElements.size() == 0)		// check for condition if operated MyGrid object is an empty matrix
	{
		return -gridB;				// in which case, return the grid being added
	}

	if (gridB.gridElements.size() == 0)		// check for condition if input MyGrid object is an empty matrix
	{
		return gridA;				// in which case, return the original grid
	}

	// refer to attached Excel file and scratch work for full explanation of logic
	if (gridB.myX < gridA.myX)
	{
		newGrid.myX = gridB.myX;
	}
	else
	{
		newGrid.myX = gridA.myX;
	}

	if (gridB.myY > gridA.myY)
	{
		newGrid.myY = gridB.myY;
	}
	else
	{
		newGrid.myY = gridA.myY;
	}

	newGrid.m_numRows = newGrid.myY - gridA.myY + gridA.m_numRows;
	newGrid.m_numCols = gridB.myX + gridB.m_numCols - newGrid.myX;

	newGrid.zeroOutGrid();

	long startColumnA = newGrid.myX - gridA.myX;	// relative location myX of grid A in the new master grid (start location of columns)
	long startRowA = newGrid.myY - gridA.myY;		// relative location myY of grid A in the new master grid (start location of rows)
	long startColumnB = gridB.myX - newGrid.myX;	// relative location myX of grid B in the new master grid (start location of columns)
	long startRowB = gridB.myY - newGrid.myY;		// relative location myY of grid B in the new master grid (start location of rows)

	long endColumnA = startColumnA + gridA.m_numCols - 1;	// relative end location of grid A's columns in the new master grid
	long endRowA = startRowA + gridA.m_numRows - 1;			// relative end location of grid A's rows in the new master grid
	long endColumnB = startColumnB + gridB.m_numCols - 1;	// relative end location of grid A's columns in the new master grid
	long endRowB = startRowB + gridB.m_numRows - 1;			// relative end location of grid A's rows in the new master grid

	bool Aactive = false;	// this will determine whether gridA has an element in the newGrid at a certain location (newGrid.gridElements[i][j])
	bool Bactive = false;	// this will determine whether gridB has an element in the newGrid at a certain location
	bool ABactive = false;	// this will determine whether gridA AND gridB have an element in the newGrid at a certain location

	for (long iRow = 0; iRow < newGrid.m_numRows; ++iRow)
	{
		for (long jCol = 0; jCol < newGrid.m_numCols; ++jCol)
		{
			Aactive = (iRow >= startRowA && jCol >= startColumnA && iRow <= endRowA && jCol <= endColumnA);	// determines whether A is "active" using its relative location of elements in the master coorinate system to the newGrid's elements
			Bactive = (iRow >= startRowB && jCol >= startColumnB && iRow <= endRowB && jCol <= endColumnB); // determines whether B is "active" using its relative location of elements in the master coorinate system to the newGrid's elements
			ABactive = Aactive && Bactive;		// if both above are true, then both grids have elements at these coordinates

			if (ABactive)
			{
				newGrid.gridElements[iRow][jCol] = gridA.gridElements[iRow - startRowA][jCol - startColumnA] - gridB.gridElements[iRow - startRowB][jCol - startColumnB];
			}
			else if (Aactive)
			{
				newGrid.gridElements[iRow][jCol] = gridA.gridElements[iRow - startRowA][jCol - startColumnA];
			}
			else if (Bactive)
			{
				newGrid.gridElements[iRow][jCol] = -gridB.gridElements[iRow - startRowB][jCol - startColumnB];
			}
			else
			{
				newGrid.gridElements[iRow][jCol] = 0;
			}
		}
	}
	return newGrid;
}

////////////////////////////////////////////////////////
// ADDITION OPERATOR WITH LONG			myGrid - long
//******************************************************
// Add long to each element in the gridElements vector
//*****************************************************
MyGrid MyGrid::operator+(long const& numLong) const
{
	MyGrid newGrid;
	newGrid.myX = this->myX;
	newGrid.myY = this->myY;
	newGrid.m_numRows = this->m_numRows;
	newGrid.m_numCols = this->m_numCols;
	newGrid.zeroOutGrid();

	MyGrid currentGrid = *this;

	for (long i = 0; i < currentGrid.m_numRows; ++i)
	{
		for (long j = 0; j < currentGrid.m_numCols; ++j)
		{
			newGrid.gridElements[i][j] = currentGrid.gridElements[i][j] + numLong;
		}
	}
	return newGrid;
}

/////////////////////////////////////////////////////////////
// OBJECT ADDITION += OPERATOR		newGrid += myGrid;
//************************************************************
// Adds MyGrid object to this MyGrid object with += operator
/////////////////////////////////////////////////////////////
MyGrid& MyGrid::operator+=(MyGrid const& rhs)
{
	*this = *this + rhs;
	return *this;
}

////////////////////////////////////////////////////////
// PREFIX ADDITION OPERATOR					++myGrid
//******************************************************
// Increases all gridElements in MyGrid object by 1
////////////////////////////////////////////////////////
MyGrid& MyGrid::operator++() // Prefix
{
	MyGrid currentGrid = *this;			// the grid being operated on

	for (long i = 0; i < currentGrid.m_numRows; ++i)
	{
		for (long j = 0; j < currentGrid.m_numCols; ++j)
		{
			this->gridElements[i][j] = currentGrid.gridElements[i][j] + 1;	// add 1 to this object's elements
		}
	}
	return *this;						// return this object as updated, since it is prefix operation
}

////////////////////////////////////////////////////////
// POSTFIX ADDITION OPERATION				myGrid++  
//******************************************************
// Increases all gridElements in MyGrid object by 1  
////////////////////////////////////////////////////////
MyGrid MyGrid::operator++(int) // Postfix
{
	MyGrid newGrid = *this; 		// the returned object resulting from adding 1 to each element of the grid operated on
	newGrid.zeroOutGrid();			// zero out the grid 
	MyGrid currentGrid = *this;		// the current grid of this object

	for (long i = 0; i < currentGrid.m_numRows; ++i)
	{
		for (long j = 0; j < currentGrid.m_numCols; ++j)
		{
			newGrid.gridElements[i][j] = currentGrid.gridElements[i][j] + 1;	// add 1 to newGrid object's elements
		}
	}
	this->gridElements = newGrid.gridElements;		// set this object's gridElements to the newGrid object's gridElements
	return currentGrid;								// RETURN the newGrid object; this object is updated but not returned in postfix
}

////////////////////////////////////////////////////////
// PREFIX SUBTRACTION OPERATOR				--myGrid
//******************************************************
// Decreases all gridElements in MyGrid object by 1
////////////////////////////////////////////////////////
MyGrid& MyGrid::operator--() // Prefix
{
	MyGrid currentGrid = *this; // the grid being operated on

	for (long i = 0; i < currentGrid.m_numRows; ++i)
	{
		for (long j = 0; j < currentGrid.m_numCols; ++j)
		{
			this->gridElements[i][j] = currentGrid.gridElements[i][j] - 1;
		}
	}
	return *this;			// return reference to this object
}

////////////////////////////////////////////////////////
// PREFIX SUBTRACTION OPERATOR				myGrid--
//******************************************************
// Decreases all gridElements in MyGrid object by 1
////////////////////////////////////////////////////////
MyGrid MyGrid::operator--(int) // Postfix
{

	MyGrid newGrid = *this; 			// the returned object resulting from adding 1 to each element of the grid operated on
	newGrid.zeroOutGrid();
	MyGrid currentGrid = *this; // the grid being operated on

	for (long i = 0; i < currentGrid.m_numRows; ++i)
	{
		for (long j = 0; j < currentGrid.m_numCols; ++j)
		{
			newGrid.gridElements[i][j] = currentGrid.gridElements[i][j] - 1;
		}
	}
	this->gridElements = newGrid.gridElements;
	return currentGrid;
}

////////////////////////////////////////////////////////
// NEGATIVE OPERATOR ON OBJECT				-myGrid
//******************************************************
// Multiplies all elements in the gridElements by 1
////////////////////////////////////////////////////////
MyGrid MyGrid::operator-() const
{
	MyGrid newGrid = *this; 	// resulting grid after multiplying the grid operated on by (-1)
	newGrid.zeroOutGrid();
	MyGrid thisGrid(*this);		// the grid being operated on

	for (long i = 0; i < thisGrid.m_numRows; ++i)
	{
		for (long j = 0; j < thisGrid.m_numCols; ++j)
		{
			newGrid.gridElements[i][j] = -thisGrid.gridElements[i][j];
		}
	}
	return newGrid;
}

///////////////////////////////////////////////////////////
// BOOLEAN OPERATOR w/ MYGRID OBJECTS	 ? gridA == gridB
//*********************************************************
///////////////////////////////////////////////////////////
// Test if two MyGrid objects are equal to each other
////////////////////////////////////////////////////////////
bool MyGrid::operator==(MyGrid const& testGrid) const
{
	MyGrid thisGrid = *this;
	if (thisGrid.myX != testGrid.myX)
	{
		return false;
	}
	else if (thisGrid.myY != testGrid.myY)
	{
		return false;
	}
	else if (thisGrid.m_numRows != testGrid.m_numRows)
	{
		return false;
	}
	else if (thisGrid.m_numCols != testGrid.m_numCols)
	{
		return false;
	}
	else
	{
		for (long i = 0; i < thisGrid.m_numRows; ++i)
		{
			for (long j = 0; j < thisGrid.m_numCols; ++j)
			{
				if (thisGrid.gridElements[i][j] != testGrid.gridElements[i][j])
				{
					return false;
				}
			}
		}
	}
	return true;
}

// Friend function, adds a MyGrid object to a long. 
// The long value is added to all the elements in the MyGrid object
MyGrid operator+(long const& lhs, MyGrid const& rhs)
{
	MyGrid newGrid = rhs;
	for (long i = 0; i < rhs.m_numRows; ++i)
	{
		for (long j = 0; j < rhs.m_numCols; ++j)
		{
			newGrid.gridElements[i][j] = rhs.gridElements[i][j] + lhs;
		}
	}
	return newGrid;
}

// Friend function, File stream insertion operator
fstream& operator<<(fstream& os, const MyGrid& gridIn)
{
	string delim = " ";
	string newL = "\n";
	os << gridIn.myX << delim << gridIn.myY << newL;
	os << gridIn.m_numRows << delim << gridIn.m_numCols << newL;

	for (long i = 0; i < gridIn.m_numRows; ++i)
	{
		for (long j = 0; j < gridIn.m_numCols; ++j)
		{
			if (j == (gridIn.m_numCols - 1))
			{
				os << gridIn.gridElements[i][j];		// don't add a space delimiter if at end of line (= number of columns)
			}
			else
			{
				os << gridIn.gridElements[i][j] << delim; // add a space after a value if not an end of line
			}
		}
		os << newL; // create a new line after each for loop of the columns for one row
	}
	return os;
}
