#ifndef _BOARD_H
#define _BOARD_H

#include "Vector.h"
#include <vector>

class Board
{
public:
	Board(const Vector Dimensions);

private:
	Vector Dimensions;
	std::vector<std::vector<char>> Grid;
};

#endif