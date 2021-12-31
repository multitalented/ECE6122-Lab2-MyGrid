/*
Author: Deanna Gierzak
Class: ECE 6122
Last Date Modified: 9/28/2020

Description:

This is the header file for MyGrid class
myX myY
nRows nCols
[] [] []----numCols
[] .
.	 .
.		.
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

#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

// see MyGrid.cpp for function comments
class MyGrid
{
private:
	long myX, myY;
	vector<vector<long>> gridElements;
	long m_numRows, m_numCols;
public:
	MyGrid()
	{
		m_numRows = 0;
		m_numCols = 0;
		myX = 0;
		myY = 0;
		vector<vector<long>> gridElements;
	}

	bool loadGridFromFile(const string& filename);
	void zeroOutGrid();
	long getNumRows() const;
	long getNumCols() const;

	MyGrid operator+(MyGrid const&) const;
	MyGrid operator-(MyGrid const&) const;

	MyGrid operator+(long const&) const;

	friend MyGrid operator+(long const& lhs, MyGrid const& rhs);

	MyGrid& operator+=(MyGrid const&);

	MyGrid& operator++(); // Prefix
	MyGrid operator++(int); // Postfix

	MyGrid& operator--(); // Prefix
	MyGrid operator--(int); // Postfix

	MyGrid operator-() const;

	bool operator==(MyGrid const&) const;

	friend fstream& operator<<(fstream& os, const MyGrid& gridIn);

};

