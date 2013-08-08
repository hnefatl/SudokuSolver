#include "SudokuSolver.h"
#include <iostream>

SudokuSolver::SudokuSolver()
{
	MakeAssumptionsIfStuck=true;
	UseMRV=true;
}

bool SudokuSolver::Load(std::string PathToFile)
{
	return Main.Load(PathToFile);
}

bool SudokuSolver::Solve()
{
	std::cout<<"Starting first phase calculations...";
	// Preprocess the Sudoku
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
	std::cout<<"Done."<<std::endl;
	// Check if the sudoku is complete after the preprocessing stage
	if(Main.IsComplete())
	{
		return true;
	}
	// If we aren't to do any further processing, return false
	if(!MakeAssumptionsIfStuck)
	{
		return Main.IsComplete();
	}

	// Otherwise, start making assumptions and processing them until solution is found or no solution is possible
	std::cout<<"Starting second phase calculations...";
	bool Result=MakeAssumption(&Main);
	std::cout<<"Done."<<std::endl<<std::endl;
	return Result;
}

bool SudokuSolver::MakeAssumption(Sudoku *Board)
{
	if(Board->IsComplete())
	{
		Main=*Board;
		return true;
	}

	Sudoku Local=*Board; // A copy of the Board at this moment in time
	Vector Position=FindUnsolvedCell(&Local); // An unsolved Cell's location
	if(Position==Vector(-1, -1))
	{
		// Sudoku solved
		return true;
	}

	for(unsigned int x=0; x<Local.Board[Position.Y][Position.X].Domain.size(); x++)
	{
		Local.SetCellValue(Position, Local.Board[Position.Y][Position.X].Domain[x]);
		// If the position is now arc-conistent
		if(EnforceArcConsistency(&Local, Position))
		{
			// Make an assumption on it
			if(MakeAssumption(&Local))
			{
				// If MakeAssumption returns true, the problem is solved
				return true;
			}
		}
		Local=*Board; // Copy the original
	}

	// If no values work, the Sudoku is broken - return false to begin the back chaining
	return false;
}

bool SudokuSolver::EnforceArcConsistency(Sudoku *Board, Vector Position)
{
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
		if(Board->Board[UpdatedPositions[x].Y][UpdatedPositions[x].X].Value==0)
		{
			// Empty domain
			if(Board->Board[UpdatedPositions[x].Y][UpdatedPositions[x].X].Domain.size()==0)
			{
				return false;
			}
			// Singleton domain
			else if(Board->Board[UpdatedPositions[x].Y][UpdatedPositions[x].X].Domain.size()==1)
			{
				Board->SetCellValue(UpdatedPositions[x], Board->Board[UpdatedPositions[x].Y][UpdatedPositions[x].X].Domain[0]);
			}
			// Failed later consistency check
			if(!EnforceArcConsistency(Board, UpdatedPositions[x]))
			{
				return false;
			}
		}
	}

	return true;
}

Vector SudokuSolver::FindUnsolvedCell(const Sudoku *Board)
{	
	if(UseMRV)
	{
		Vector Position; // Holds the position of the Cell with the smallest domain
		// Find Cell with least possible values
		unsigned int SmallestDomain=9;
		for(unsigned int y=0; y<9; y++)
		{
			for(unsigned int x=0; x<9; x++)
			{
				if(Board->Board[y][x].Domain.size()>1) // Not empty or already found
				{
					if(Board->Board[y][x].Domain.size()<SmallestDomain) // Improvement on current smallest domain
					{
						SmallestDomain=Board->Board[y][x].Domain.size();
						Position=Vector(x, y);
						if(SmallestDomain==2)
						{
							// No possible improvement
							return Position;
						}
					}
				}
			}
		}

		return Position;
	}
	else
	{
		// Find first unsolved cell
		for(unsigned int y=0; y<9; y++)
		{
			for(unsigned int x=0; x<9; x++)
			{
				// Unsolved cell
				if(Board->Board[y][x].Value>1)
				{
					return Vector(x, y);
				}
			}
		}
	}

	// Shouldn't really be able to reach this point - asking for an unsolved Cell in a solved Sudoku
	return Vector(-1, -1);
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