#include "Sudoku.h"

#include <fstream>

Sudoku::Sudoku()
	:Complete(false)
{
}

bool Sudoku::Load(std::string PathToFile)
{	
	std::ifstream In(PathToFile);
	if(!In.good())
	{
		return false;
	}

	// Read in board from file
	Board.push_back(std::vector<Cell>());
	char Temp;
	while(In.get(Temp))
	{
		if(Temp=='\n')
		{
			Board.push_back(std::vector<Cell>());
		}
		else
		{
			Board[Board.size()-1].push_back(atoi(&Temp));
		}
	}

	// Validate board
	if(Board.size()==0)
	{
		// Invalid board
		return false;
	}

	int Size=Board[0].size();
	for(unsigned int y=0; y<Board.size(); y++)
	{
		if(Board[y].size()!=Size)
		{
			// Not regularly shaped
			return false;
		}
	}

	return true;
}
bool Sudoku::Load(std::vector<std::vector<Cell>> Board)
{
	this->Board=Board;

	return true;
}

void Sudoku::operator=(Sudoku One)
{
	Board=One.Board;
}

bool Sudoku::IsComplete()
{
	return Complete;
}
void Sudoku::SetComplete(bool Complete)
{
	this->Complete=Complete;
}

void Sudoku::Print()
{
	for(unsigned int y=0; y<9; y++)
	{
		for(unsigned int x=0; x<9; x++)
		{
			if(Board[y][x].Value!=0)
			{
				std::cout<<Board[y][x].Value;
			}
			else
			{
				std::cout<<"_";
			}
		}
		std::cout<<std::endl;
	}
}