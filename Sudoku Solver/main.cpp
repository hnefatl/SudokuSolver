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

	Solver.Solve();

	if(Solver.GetSudoku().IsComplete())
	{
		std::cout<<"Sudoku completed:"<<std::endl;
	}
	else
	{
		std::cout<<"Sudoku uncompleted:"<<std::endl<<std::endl;
	}

	for(unsigned int y=0; y<9; y++)
	{
		for(unsigned int x=0; x<9; x++)
		{
			if(Solver.GetSudoku().Board[y][x].Value!=0)
			{
				std::cout<<(unsigned int)Solver.GetSudoku().Board[y][x].Value;
			}
			else
			{
				std::cout<<"_";
			}
		}
		std::cout<<std::endl;
	}

	std::cout<<std::endl<<"Press any key to continue...";
	_getch();

	return 0;
}