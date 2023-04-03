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
	int timeoutCount = 0;
	
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
							{
								std::cout << "Tile falsly flagged at " << t->x << ", " << t->y << std::endl;
								return false;
							}
						}
						curTile->state = TileState::finished;
						if (curTile->field != nullptr)
						{
							curTile->removeAmbigField();
						}
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
								{
									std::cout << "Bomb falsly clicked at " << t->x << ", " << t->y << std::endl;
									return false;
								}
							}
						}
						curTile->state = TileState::finished;
						if (curTile->field != nullptr)
						{
							curTile->removeAmbigField();
						}
						timeout = false;
						continue;
					}


					

					//more complex cases when ambiguity for one can provide some info for a neighbooring tile

					if (curTile->countNearUnknown() - curTile->value == 1) //one more tile than needed, ambiguous position
					{
						curTile->createAmbigField();
						timeout = false;
						continue;
					}


					//check for surrounding tiles with abiguous fields, then process if anything can be cleared or marked from it
					for (Tile* nearT : curTile->near)
					{

						if (nearT != nullptr && nearT->state == TileState::cleared && nearT->field != nullptr)
						{
							AmbigField* ambField = nearT->field;
							std::vector<Tile*> inField = std::vector<Tile*>();

							//check if current tile contains 2 tiles of the ambiguous field
							int matchCount = 0;
							for (Tile* adj : curTile->near) //probably could find more efficient method
							{
								for (Tile* fieldT : ambField->tiles)
								{
									if (adj != nullptr && adj == fieldT) //pointer comparison could cause problems maybe
									{
										matchCount++;
										inField.push_back(adj);
									}
								}
							}

							if (matchCount == 2 && curTile->countNearUnknown() != 2)
							{
								//if ambiguous segment would complete flagged 
								if (curTile->countNearFlagged() + 1 == curTile->value)
								{
									std::cout << "before trying to clear around " << curTile->x << ", " << curTile->y << std::endl;
									board.PrintVisibleBoard();
									for (Tile* t : curTile->near)
									{
										if (t != nullptr && t != inField[0] && t != inField[1] && t->state == TileState::unknown) //if not part of ambigField
										{
											bool check = board.click(t->x, t->y);
											if (!check) //if bomb clicked
											{
												std::cout << "Bomb falsly clicked at " << t->x << ", " << t->y << std::endl;
												return false;
											}
											
										}
									}
									timeout = false;
									continue;
								}
								else if ((curTile->countNearUnknown() - 1) + curTile->countNearFlagged() == curTile->value)
								{
									//if remaining unknown + already flagged + the ambiguous fill, flag remaining unknown
									for (Tile* t : curTile->near)
									{
										std::cout << "before trying to flag around " << curTile->x << ", " << curTile->y << std::endl;
										board.PrintVisibleBoard();
										if (t != nullptr && t != inField[0] && t != inField[1] && t->state == TileState::unknown) //if not part of ambigField
										{
											bool check = board.flag(t->x, t->y);
											if (!check) //if not bomb flagged
											{
												std::cout << "Tile falsly flagged at " << t->x << ", " << t->y << std::endl;
												return false;
											}
											
										}
									}
									timeout = false;
									continue;

								}

							}


						}
					}



				}
			}
		}
		if (timeout)
		{		
			timeoutCount++;
		}
		else
		{
			timeoutCount = 0;
		}
		if (timeoutCount >= 3) //give solver a few more cycles incase of weird cases maybe
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
