#ifndef _SUDOKUSOLVER_H
#define _SUDOKUSOLVER_H

#include <string>
#include <vector>

#include "Sudoku.h"
#include "Cell.h"

class SudokuSolver
{
public:
	SudokuSolver();

	bool Load(std::string PathToFile);

	bool Solve();

	Sudoku GetSudoku();

	bool MakeAssumptionsIfStuck;
	bool UseMRV;

private:
	// Picks a Cell to modify, and changes it until it works or breaks.
	// Returns true on finished Sudoku, false on failed Sudoku
	bool MakeAssumption(Sudoku *Board);
	// Returns true if the Position is now Arc consistent
	bool EnforceArcConsistency(Sudoku *Board, Vector Position);

	Vector FindUnsolvedCell(const Sudoku *Board);

	int Contains(unsigned short Value, std::vector<unsigned short> Domain);

private:
	Sudoku Main;
};

#endif