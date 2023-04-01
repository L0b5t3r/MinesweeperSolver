#include "Solver.h"
#include <ctime>

Solver::Solver()
{
	Board board();
	srand((unsigned)time(NULL));
}


bool Solver::Run()
{
	int startX = rand() % board.height;
	int startY = rand() % board.width;

	bool safe = true;

	while (board.trueGrid[startX][startY]->value != 0) //ensure starts on 0 spot
	{
		startX = rand() % board.height;
		startY = rand() % board.width;
	}

	board.click(startX, startY);

	bool timeout = true; //timeout loop if no action occurred, stuck
	
	while (safe) //main solving loop, pass all tiles and see if action can be taken
	{
		timeout = true;
		for (int x = 0; x < board.height; x++)
		{
			for (int y = 0; y < board.width; y++)
			{
				Tile* curTile = board.visibleGrid[x][y];

				if (curTile->state == TileState::cleared)
				{

					//first check if tile has the same number of unknown near tiles as its value, mark tiles
					std::vector<Tile*> tilesLeft = std::vector<Tile*>();
					for (Tile* t : curTile->near)
					{
						if (t != nullptr && t->state == TileState::unknown)
						{
							tilesLeft.push_back(t);
						}
					}
					if (tilesLeft.size() == curTile->value) 
					{
						for (Tile* t : tilesLeft)
						{
							bool check = board.flag(t->x, t->y);
							if (!check) //bad flag
								return false;
						}
						timeout = false;
					}


					//check if tile has value number of marked mines on near tiles, clear rest

				}
			}
		}
		if (timeout)
		{
			return false;
		}
	}
	
	return true;
}

void Solver::CreateBoard(int h, int w, int n)
{
	board.InitializeBoard(h, w, n);
	board.PrintVisibleBoard();
	board.PrintTrueBoard();
}

void Solver::PrintBoard()
{
	board.PrintVisibleBoard();
	board.PrintTrueBoard();
}

Solver::~Solver() {}
