#include "Board.h"
#include <ctime>
#include <iostream>

Board::Board()
{
	srand((unsigned)time(NULL));
}

void Board::InitializeBoard(int h, int w, int n)
{
	height = h;
	width = w;
	totalMines = n;
	remainingMines = n;

	trueGrid = std::vector<std::vector<Tile>>(h, std::vector<Tile>(w, Tile()));

	for (int i = 0; i < n; i++) //create and place n mines at random positions
	{
		int rh = rand() % h;
		int rw = rand() % w;
		if (trueGrid[rh][rw].value == 0)
		{
			trueGrid[rh][rw].value = -1; 
		}
	}

}


void Board::PrintTrueBoard()
{
	system("cls");
	std::cout << "Total Mines: " << totalMines << "\t\t Remaining Mines: " << remainingMines << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int o = 0; o < width; o++)
		{
			if(trueGrid[i][o].value == -1) //adjust spacing for negative
				std::cout << trueGrid[i][o].value << "  ";
			else
				std::cout << " " << trueGrid[i][o].value << "  ";
			
		}
		std::cout << std::endl;
	}
}


Board::~Board() {}