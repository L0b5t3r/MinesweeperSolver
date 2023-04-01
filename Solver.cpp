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


	while (board.trueGrid[startX][startY]->value != 0) //ensure starts on 0 spot
	{
		startX = rand() % board.height;
		startY = rand() % board.width;
	}

	board.click(startX, startY);

	bool timeout = true; //timeout loop if no action occurred, stuck
	
	while (true) //main solving loop, pass all tiles and see if action can be taken
	{
		timeout = true;
		for (int x = 0; x < board.height; x++)
		{
			for (int y = 0; y < board.width; y++)
			{
				Tile* curTile = board.visibleGrid[x][y];

				if (board.remainingMines <= 0) //all mines found
					return true;

				if (curTile->state == TileState::cleared)
				{
					int markedCount = 0;

					//first check if tile has the same number of unknown near tiles as its value, mark tiles
					std::vector<Tile*> tilesLeft = std::vector<Tile*>();
					for (Tile* t : curTile->near)
					{
						if (t != nullptr && (t->state == TileState::unknown || t->state == TileState::marked))
						{
							tilesLeft.push_back(t);
							
							if (t->state == TileState::marked) //count marked for next check
								markedCount++; 
						}
					}

					if (tilesLeft.size() == curTile->value) //action, flag surrounding tiles
					{
						for (Tile* t : tilesLeft)
						{
							bool check = board.flag(t->x, t->y);
							if (!check) //bad flag
								return false;
						}
						curTile->state = TileState::finished;
						timeout = false; 
						continue; //tile finished, no other checks can be made
					}


					//check if tile has value number of marked mines on near tiles, clear rest
					if (markedCount == curTile->value)
					{
						for (Tile* t : tilesLeft)
						{
							if (t->state == TileState::unknown)
							{
								bool check = board.click(t->x, t->y);
								if (!check) //if bomb clicked
									return false;
							}
						}
						curTile->state = TileState::finished;
						timeout = false;
						continue;
					}


				}
			}
		}
		if (timeout)
		{
			board.PrintVisibleBoard();
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
