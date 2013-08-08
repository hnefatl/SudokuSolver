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
	std::cout<<std::endl;
#else
	Path="Sudoku.txt";
#endif

	SudokuSolver Solver;
	std::cout<<"Loading Sudoku...";
	if(!Solver.Load(Path))
	{
		std::cout<<"Failed."<<std::endl;
		std::cout<<"Press any key to continue...";
		_getch();
		return 1;
	}
	std::cout<<"Done."<<std::endl;

	if(!Solver.Solve())
	{
		std::cout<<"Sudoku failed."<<std::endl;
	}

	if(Solver.GetSudoku().IsComplete())
	{
		std::cout<<std::endl<<"Sudoku completed:"<<std::endl;
	}
	else
	{
		std::cout<<std::endl<<"Sudoku uncompleted:"<<std::endl<<std::endl;
	}

	Solver.GetSudoku().Print();

	std::cout<<std::endl<<std::endl<<"Press any key to continue...";
	_getch();

	return 0;
}