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

	trueGrid = std::vector<std::vector<Tile*>>(h, std::vector<Tile*>(w));
	visibleGrid = std::vector<std::vector<Tile*>>(h, std::vector<Tile*>(w));

	for (int i = 0; i < n; i++) //create and place n mines at random positions
	{
		int rh = rand() % h;
		int rw = rand() % w;
		if (trueGrid[rh][rw] == nullptr)
		{
			trueGrid[rh][rw] = new Tile(-1);
		}
	}

	for (int i = 0; i < height; i++) //initialize remaining tiles count and local tile pointers
	{
		for (int o = 0; o < width; o++)
		{
			visibleGrid[i][o] = new Tile(); //each tile of the visible list starts as unknown

			if (trueGrid[i][o] == nullptr) //if no existing tile/mine
			{
				trueGrid[i][o] = new Tile(0);
			}

			//initialize tile's local pointers
			if (i > 0) //if not top
			{
				trueGrid[i][o]->up = trueGrid[i - 1][o];
				if(o > 0)
					trueGrid[i][o]->upLeft = trueGrid[i - 1][o - 1];
				if(o < width - 1)
					trueGrid[i][o]->upRight = trueGrid[i - 1][o + 1];
			}
			if (i < height - 1) //if not bottom
			{
				trueGrid[i][o]->down = trueGrid[i + 1][o];
				if (o > 0)
					trueGrid[i][o]->downLeft = trueGrid[i + 1][o - 1];
				if (o < width - 1)
					trueGrid[i][o]->downRight = trueGrid[i + 1][o + 1];
			}
			if (o > 0) //if not left edge
			{
				trueGrid[i][o]->left = trueGrid[i][o - 1];
			}
			if (o < width - 1)
			{
				trueGrid[i][o]->right = trueGrid[i][o + 1];
			}

			trueGrid[i][o]->updateNearTiles(); //pointers were not being updated properly on their own, maybe check later

			if (trueGrid[i][o]->value != -1) //if not a mine, count nearby mines
			{
				trueGrid[i][o]->value = trueGrid[i][o]->countNearMines();
			}
		}
	}

}

void setNearTiles(Tile* t)
{

}


void Board::PrintTrueBoard()
{
	//system("cls");
	std::cout << "Total Mines: " << totalMines << "\t\t Remaining Mines: " << remainingMines << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int o = 0; o < width; o++)
		{
			if(trueGrid[i][o]->value == -1)
				std::cout << " b ";
			else
				std::cout << " " << trueGrid[i][o]->value << " ";
			
		}
		std::cout << std::endl << std::endl;
	}
}

void Board::PrintVisibleBoard()
{
	system("cls");
	std::cout << "Total Mines: " << totalMines << "\t\t Remaining Mines: " << remainingMines << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int o = 0; o < width; o++)
		{
			switch (visibleGrid[i][o]->state)
			{
			case TileState::unknown:
				std::cout << " x ";
				break;
			case TileState::cleared:
				std::cout << " " << visibleGrid[i][o]->value << " ";
				break;
			case TileState::marked:
				std::cout << " b ";
				break;
			case TileState::finished:
				std::cout << " x ";
				break;
			}

		}
		std::cout << std::endl;
	}
}

Board::~Board() {}