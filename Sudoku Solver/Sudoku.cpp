#include "Sudoku.h"

#include <fstream>

Sudoku::Sudoku()
	:TotalCells(0),
	FilledCells(0)
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
			if(atoi(&Temp)>0)
			{
				// Filled value
				FilledCells++;
			}
		}
	}
	In.close();

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

	TotalCells=Board.size()*Board[0].size();

	return true;
}

void Sudoku::SetCellValue(Vector Position, unsigned short Value)
{
	Board[Position.Y][Position.X].Value=Value;
	Board[Position.Y][Position.X].Domain.clear();
	Board[Position.Y][Position.X].Domain.push_back(Value);
	FilledCells++;
}

void Sudoku::operator=(Sudoku One)
{
	TotalCells=One.TotalCells;
	FilledCells=One.FilledCells;

	Board.clear();
	Board.resize(One.Board.size());
	for(unsigned int y=0; y<One.Board.size(); y++)
	{
		Board[y].resize(One.Board[0].size());
	}

	for(unsigned int y=0; y<One.Board.size(); y++)
	{
		for(unsigned int x=0; x<One.Board[y].size(); x++)
		{
			Board[y][x]=One.Board[y][x];
		}
	}
}

bool Sudoku::IsComplete()
{
	return FilledCells==TotalCells;
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