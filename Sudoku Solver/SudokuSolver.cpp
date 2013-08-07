#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(std::string PathToFile)
{
	Main.Load(PathToFile);
}

void SudokuSolver::Solve()
{	
	for(unsigned int y=0; y<9; y++)
	{
		for(unsigned int x=0; x<9; x++)
		{
			EnforceArcConsistency(&Main, Vector(x, y));
		}
	}
}

bool SudokuSolver::EnforceArcConsistency(Sudoku *Board, Vector Position)
{
	if(Board->Board[Position.Y][Position.X].Value==0)
	{
		// No set value - no point in enforcing, but no error either
		return true;
	}
	// Enforce arc consistency for this position, storing all affected neighbours
	std::vector<Vector> UpdatedPositions;

	// Traverse column
	for(unsigned int y=0; y<9; y++)
	{
		if(y!=Position.Y)
		{
			if(Board->Board[y][Position.X].Value==0)
			{
				int Location=Contains(Board->Board[Position.Y][Position.X].Value, Board->Board[y][Position.X].Domain);
				if(Location!=-1)
				{
					// Number found - erase from Domain
					Board->Board[y][Position.X].Domain.erase(Board->Board[y][Position.X].Domain.begin()+Location);
					UpdatedPositions.push_back(Vector(y, Position.X));
				}
			}
		}
	}
	// Traverse row
	for(unsigned int x=0; x<9; x++)
	{
		if(x!=Position.X)
		{
			if(Board->Board[Position.Y][x].Value==0)
			{
				int Location=Contains(Board->Board[Position.Y][Position.X].Value, Board->Board[Position.Y][x].Domain);
				if(Location!=-1)
				{
					// Number found - erase from Domain
					Board->Board[Position.Y][x].Domain.erase(Board->Board[Position.Y][x].Domain.begin()+Location);
					UpdatedPositions.push_back(Vector(Position.Y, x));
				}
			}
		}
	}
	// Traverse box
	for(unsigned int y=(Position.Y%3)*3; y<((Position.Y%3)*3)+3; y++)
	{
		for(unsigned int x=(Position.X%3)*3; x<((Position.X%3)*3)+3; x++)
		{
			if(y!=Position.Y && x!=Position.X)
			{
				if(Board->Board[y][y].Value==0)
				{
					int Location=Contains(Board->Board[Position.Y][Position.X].Value, Board->Board[y][x].Domain);
					if(Location!=-1)
					{
						// Number found - erase from Domain
						Board->Board[y][x].Domain.erase(Board->Board[y][x].Domain.begin()+Location);
						UpdatedPositions.push_back(Vector(y, x));
					}
				}
			}
		}
	}

	// Process each updated position
	for(unsigned int x=0; x<UpdatedPositions.size(); x++)
	{
		// Empty domain
		if(Board->Board[UpdatedPositions[x].Y][UpdatedPositions[x].X].Domain.size()==0)
		{
			return false;
		}
		// Failed later consistency check
		if(!EnforceArcConsistency(Board, UpdatedPositions[x]))
		{
			return false;
		}
	}

	return true;
}

int SudokuSolver::Contains(unsigned short Value, std::vector<unsigned short> Domain)
{
	// Assume Domain of cells is ordered, so run binary search
	unsigned int Low=0, High=Domain.size(), Middle=(Low+High)/2;
	while(Low!=Middle && Low!=High)
	{
		if(Value==Domain[Middle])
		{
			return Middle;
		}
		else if(Value<Domain[Middle])
		{
			High=Middle;
		}
		else if(Value>Domain[Middle])
		{
			Low=Middle;
		}
		// Change must have been made or location found, update middle
		Middle=(Low+High)/2;
	}

	return -1;
}

Sudoku SudokuSolver::GetSudoku()
{
	return Main;
}