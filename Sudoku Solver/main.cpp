#include <iostream>

#include "SudokuSolver.h"

#include <string>
#include <conio.h>

int main(int argc, char *argv[])
{
	std::string Path;
#ifndef _DEBUG
	std::cout<<"Enter the path to the sudoku file: ";
	std::cin>>Path;
#else
	Path="Sudoku.txt";
#endif

	std::cout<<std::endl;
	std::cout<<"Loading Sudoku...";
	SudokuSolver Solver(Path);
	std::cout<<"Done."<<std::endl;

	if(!Solver.Solve())
	{
		std::cout<<"Sudoku failed."<<std::endl;
	}

	if(Solver.GetSudoku().IsComplete())
	{
		std::cout<<"Sudoku completed:"<<std::endl;
	}
	else
	{
		std::cout<<"Sudoku uncompleted:"<<std::endl<<std::endl;
	}

	Solver.GetSudoku().Print();
	_getch();

	return 0;
}