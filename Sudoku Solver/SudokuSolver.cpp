#include "SudokuSolver.h"
#include <iostream>

SudokuSolver::SudokuSolver(std::string PathToFile)
{
	Main.Load(PathToFile);
}

bool SudokuSolver::Solve()
{
	for(unsigned int y=0; y<9; y++)
	{
		for(unsigned int x=0; x<9; x++)
		{
			if(!EnforceArcConsistency(&Main, Vector(x, y)))
			{
				return false;
			}
		}
	}

	return true;
}

bool SudokuSolver::EnforceArcConsistency(Sudoku *Board, Vector Position)
{
	// Empty domain
	if(Board->Board[Position.Y][Position.X].Domain.size()==0)
	{
		return false;
	}
	// Singleton domain
	else if(Board->Board[Position.Y][Position.X].Domain.size()==1)
	{
		Board->Board[Position.Y][Position.X].Value=Board->Board[Position.Y][Position.X].Domain[0];
	}
	if(Board->Board[Position.Y][Position.X].Value==0)
	{
		// No point in processing
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
					UpdatedPositions.push_back(Vector(Position.X, y));
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
					UpdatedPositions.push_back(Vector(x, Position.Y));
				}
			}
		}
	}
	// Traverse box
	for(unsigned int y=(Position.Y/3)*3; y<((Position.Y/3)*3)+3; y++)
	{
		for(unsigned int x=(Position.X/3)*3; x<((Position.X/3)*3)+3; x++)
		{
			// If not the same cell as currently working
			if(y!=Position.Y && x!=Position.X)
			{
				// If unset variable
				if(Board->Board[y][x].Value==0)
				{
					// Find location of variable
					int Location=Contains(Board->Board[Position.Y][Position.X].Value, Board->Board[y][x].Domain);
					if(Location!=-1)
					{
						// Number found - erase from Domain
						Board->Board[y][x].Domain.erase(Board->Board[y][x].Domain.begin()+Location);
						UpdatedPositions.push_back(Vector(x, y));
					}
				}
			}
		}
	}

	// Process each updated position
	for(unsigned int x=0; x<UpdatedPositions.size(); x++)
	{
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
	unsigned int Low=0, High=Domain.size(), Middle;
	while(High>=Low) // Allow a last check when Low and High are 0
	{
		Middle=(Low+High)/2;
		if(Middle>=Domain.size())
		{
			// Prevent exception being thrown
			break;
		}
		if(Value==Domain[Middle])
		{
			return Middle;
		}
		else if(Value<Domain[Middle])
		{
			High=Middle-1;
		}
		else if(Value>Domain[Middle])
		{
			Low=Middle+1;
		}
	}

	return -1;
}

Sudoku SudokuSolver::GetSudoku()
{
	return Main;
}