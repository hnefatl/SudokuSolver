#ifndef _SUDOKU_H
#define _SUDOKU_H

#include "Vector.h"
#include "Cell.h"

#include <iostream>
#include <vector>

class Sudoku
{
public:
	Sudoku();

	bool Load(std::string PathToFile);
	
	void SetCellValue(Vector Position, unsigned short Value);

	void operator =(Sudoku One);

	bool IsComplete();

	void Print();

	std::vector<std::vector<Cell>> Board;

private:
	unsigned int TotalCells;
	unsigned int FilledCells;
};

#endif