#ifndef _CELL_H
#define _CELL_H

#include <vector>

class Cell
{
public:
	Cell();
	Cell(unsigned short Value);

	unsigned short Value;
	std::vector<unsigned short> Domain;
};

#endif