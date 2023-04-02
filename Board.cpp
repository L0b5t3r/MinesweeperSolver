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
			trueGrid[rh][rw] = new Tile(rh, rw, -1);
		}
		else
		{
			i--; //dont count if mine not placed
		}
	}

	for (int i = 0; i < height; i++) //initialize remaining tiles count and local tile pointers
	{
		for (int o = 0; o < width; o++)
		{
			visibleGrid[i][o] = new Tile(i, o); //each tile of the visible list starts as unknown

			if (trueGrid[i][o] == nullptr) //if no existing tile/mine
			{
				trueGrid[i][o] = new Tile(i, o, 0);
			}
			
		}
	}

	for (int i = 0; i < height; i++) //set near tiles after all have been initialized
	{
		for (int o = 0; o < width; o++)
		{
			setNearTiles(i, o);

			if (trueGrid[i][o]->value != -1) //if not a mine, count nearby mines
			{
				trueGrid[i][o]->value = trueGrid[i][o]->countNearMines();
			}
			visibleGrid[i][o]->value = trueGrid[i][o]->value; //match grid values, visible will be hidden until clicked
		}
	}
}

void Board::setNearTiles(int i, int o)
{
	//initialize tile's local pointers
	if (i > 0) //if not top
	{
		trueGrid[i][o]->up = trueGrid[i - 1][o];
		visibleGrid[i][o]->up = visibleGrid[i - 1][o];
		if (o > 0)
		{
			trueGrid[i][o]->upLeft = trueGrid[i - 1][o - 1];
			visibleGrid[i][o]->upLeft = visibleGrid[i - 1][o - 1];
		}
			
		if (o < width - 1)
		{
			trueGrid[i][o]->upRight = trueGrid[i - 1][o + 1];
			visibleGrid[i][o]->upRight = visibleGrid[i - 1][o + 1];
		}
	}
	if (i < height - 1) //if not bottom
	{
		trueGrid[i][o]->down = trueGrid[i + 1][o];
		visibleGrid[i][o]->down = visibleGrid[i + 1][o];
		if (o > 0)
		{
			trueGrid[i][o]->downLeft = trueGrid[i + 1][o - 1];
			visibleGrid[i][o]->downLeft = visibleGrid[i + 1][o - 1];
		}

		if (o < width - 1)
		{
			trueGrid[i][o]->downRight = trueGrid[i + 1][o + 1];
			visibleGrid[i][o]->downRight = visibleGrid[i + 1][o + 1];
		}			
	}
	if (o > 0) //if not left edge
	{
		trueGrid[i][o]->left = trueGrid[i][o - 1];
		visibleGrid[i][o]->left = visibleGrid[i][o - 1];
	}
	if (o < width - 1)
	{
		trueGrid[i][o]->right = trueGrid[i][o + 1];
		visibleGrid[i][o]->right = visibleGrid[i][o + 1];
	}

	trueGrid[i][o]->updateNearTiles(); //pointers were not being updated properly on their own, maybe check later
	visibleGrid[i][o]->updateNearTiles();
}



bool Board::click(int x, int y) //"click" the selected tile that is believed to be safe to uncover
{
	if (trueGrid[x][y]->value == -1) //if bomb clicked, return false to signal loss
	{
		return false;
	}

	visibleGrid[x][y]->state = TileState::cleared;
	if (trueGrid[x][y]->value == 0) 
	{
		clear0s(x, y);
	}
	return true;
}

bool Board::flag(int x, int y) //flag the selected tile as a mine, instant lose if wrong for this implementation
{
	if (trueGrid[x][y]->value != -1)
	{
		return false;
	}

	if (visibleGrid[x][y]->state == TileState::unknown)
	{
		remainingMines--;
		visibleGrid[x][y]->state = TileState::marked;
	}
	return true;
}

void Board::clear0s(int x, int y) //clear 0 tiles adjacent to the selected 0, recursive
{
	if (trueGrid[x][y]->value != 0)
		return;

	for (Tile* t : trueGrid[x][y]->near) //for all surrounding tiles, set to cleared and repeat for any found 0's
	{
		if (t != nullptr && visibleGrid[t->x][t->y]->state == TileState::unknown)
		{
			visibleGrid[t->x][t->y]->state = TileState::cleared;
			if (t->value == 0)
			{
				clear0s(t->x, t->y);
			}
		}
	}

	visibleGrid[x][y]->state = TileState::finished;
}



void Board::PrintTrueBoard()
{
	//system("cls");

	std::cout << "Total Mines: " << totalMines << "\t\t Remaining Mines: " << remainingMines << std::endl;
	for (int i = 0; i < height; i++)
	{
		for (int o = 0; o < width; o++)
		{
			/*
			if(trueGrid[i][o]->value == -1)
				std::cout << " m ";
			else
				std::cout << " " << trueGrid[i][o]->value << " ";
				*/

			switch (trueGrid[i][o]->value)
			{
			case -1:
				std::cout << "\x1B[31m m \x1B[0m"; //red
				break;
			case 0:
				std::cout << "\x1B[97m 0 \x1B[0m"; //white
				break;
			case 1:
				std::cout << "\x1B[96m 1 \x1B[0m"; //cyan
				break;
			case 2:
				std::cout << "\x1B[92m 2 \x1B[0m"; //bright green
				break;
			case 3:
				std::cout << "\x1B[91m 3 \x1B[0m"; //bright red
				break;
			case 4:
				std::cout << "\x1B[34m 4 \x1B[0m"; //blue
				break;
			case 5:
				std::cout << "\x1B[32m 5 \x1B[0m"; //green
				break;
			case 6:
				std::cout << "\x1B[35m 6 \x1B[0m"; //magenta
				break;
			case 7:
				std::cout << "\x1B[94m 7 \x1B[0m"; //bright blue
				break;
			case 8:
				std::cout << "\x1B[33m 8 \x1B[0m"; //yellow
				break;
			}
			
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
			case TileState::marked:
				std::cout << "\x1B[31m m \x1B[0m"; //red
				break;
			case TileState::cleared:
			case TileState::finished:
				switch (trueGrid[i][o]->value)
				{
				case 0:
					std::cout << "\x1B[97m 0 \x1B[0m"; //white
					break;
				case 1:
					std::cout << "\x1B[96m 1 \x1B[0m"; //cyan
					break;
				case 2:
					std::cout << "\x1B[92m 2 \x1B[0m"; //bright green
					break;
				case 3:
					std::cout << "\x1B[91m 3 \x1B[0m"; //bright red
					break;
				case 4:
					std::cout << "\x1B[34m 4 \x1B[0m"; //blue
					break;
				case 5:
					std::cout << "\x1B[32m 5 \x1B[0m"; //green
					break;
				case 6:
					std::cout << "\x1B[35m 6 \x1B[0m"; //magenta
					break;
				case 7:
					std::cout << "\x1B[94m 7 \x1B[0m"; //bright blue
					break;
				case 8:
					std::cout << "\x1B[33m 8 \x1B[0m"; //yellow
					break;
				}
				break;
			}

		}
		std::cout << std::endl << std::endl;
	}
}

Board::~Board() {}