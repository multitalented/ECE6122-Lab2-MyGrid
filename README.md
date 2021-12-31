# ECE6122-Lab2-MyGrid

Last Date Modified: 9/26/2020

	Description:

	This program takes input text files with numbers of format:

	myX myY
	nRows nCols

	(values of a matrix with nCols number of values for each row and nRows number of rows)
	myX, myY refer to the location of the MyGrid object in a global coordinate system such that

	Y_global   				___________>x
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


    Example execution in command line:
    ~$  g++ .\*.cpp a.exe
    ~$  a.exe Input1.txt Input2.txt
    ~$ cat output-file-name.txt
    
    (--series of calculated grids--)
    
