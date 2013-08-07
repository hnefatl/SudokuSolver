#ifndef _SUDOKUSOLVER_H
#define _SUDOKUSOLVER_H

#include <string>
#include <vector>

#include "Sudoku.h"
#include "Cell.h"

class SudokuSolver
{
public:
	SudokuSolver(std::string PathToFile);

	void Solve();

	Sudoku GetSudoku();

private:
	bool EnforceArcConsistency(Sudoku *Board, Vector Position);

	int Contains(unsigned short Value, std::vector<unsigned short> Domain);

	Sudoku Main;
};

#endif