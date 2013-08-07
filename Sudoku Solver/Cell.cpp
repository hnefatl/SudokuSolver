#include "Cell.h"

Cell::Cell()
	:Value(0)
{
	for(unsigned int x=1; x<=9; x++)
	{
		Domain.push_back(x);
	}
}
Cell::Cell(unsigned short Value)
	:Value(Value)
{
	if(Value==0)
	{
		for(unsigned int x=1; x<=9; x++)
		{
			Domain.push_back(x);
		}
	}
	else
	{
		Domain.push_back(Value);
	}
}