#include "Board.h"
#include <ctime>
#include <iostream>

Board::Board()
{
	srand((unsigned)time(NULL));
}

void Board::InitializeBoard(int h, int w, int n)
{
	std::vector<std::vector<Tile>> trueGrid(h, std::vector<Tile>(w, Tile()));

	for (int i = 0; i < n; i++)
	{
		int rh = rand() % h;
		int rw = rand() % w;
		//if (trueGrid[rh][rw] == );
		//trueGrid[rand() % h][rand() % w] = Tile(-1);
	}

}


void Board::PrintTrueBoard()
{
	for (int i = 0; i < height; i++)
	{
		for (int o = 0; o < width; o++)
		{
			std::cout << trueGrid[i][o].value << " ";
		}
		std::cout << std::endl;
	}
}


Board::~Board() {}