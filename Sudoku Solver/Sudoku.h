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
	bool Load(std::vector<std::vector<Cell>> Board);
	
	void operator =(Sudoku One);

	bool IsComplete();
	void SetComplete(bool Complete);

	void Print();

	std::vector<std::vector<Cell>> Board;

private:
	bool Complete;
};

#endif