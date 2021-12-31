/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 9/26/2020

Description:

This program takes input text files with numbers of format:
myX myY
nRows nCols
(values of a matrix with nCols number of values for each row and nRows number of rows)

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
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

#include "MyGrid.h"

int main(int argc, char* argv[])
{
	vector <vector<long>> v1(3, vector<long>(5));
	vector <long> v2(3, 10);
	fstream outFile("Lab2Output.txt", fstream::out);

	vector<MyGrid> vecGrids;
	MyGrid tmpGrid;

	vecGrids.resize(argc);

	for (int ii = 1; ii < argc; ii++)
	{
		if (!vecGrids[ii - 1].loadGridFromFile(argv[ii]))
		{
			outFile << "Failed to load file: " << argv[ii] << endl;
		}
	}

	if (argc >= 3)
	{
		tmpGrid.zeroOutGrid();

		tmpGrid += vecGrids[1];
		outFile << tmpGrid << endl;

		tmpGrid = vecGrids[0] + vecGrids[1];	// this works
		outFile << tmpGrid << endl;

		tmpGrid = vecGrids[0] - vecGrids[1];	// this works
		outFile << tmpGrid << endl;

		tmpGrid = vecGrids[0] + 10;				// this works
		outFile << tmpGrid << endl;

		tmpGrid = 10 + vecGrids[1] + 10;		// this works
		outFile << tmpGrid << endl;

		outFile << tmpGrid++ << endl;			// this works!
		outFile << ++tmpGrid << endl;

		outFile << tmpGrid-- << endl;			// this works
		outFile << --tmpGrid << endl;


		outFile << -tmpGrid << endl;			// this works

		if (vecGrids[0] == vecGrids[1])
		{
			outFile << "The first two grids are equal" << endl;
		}
		else
		{
			outFile << "The first two grids are not equal" << endl;
		}

		outFile << "The first grid has " << vecGrids[0].getNumRows() << " rows and " << vecGrids[0].getNumCols() << " cols." << endl;

		vecGrids[0].zeroOutGrid();
		outFile << vecGrids[0] << endl;

	}

	outFile.close();

	return 0;


}