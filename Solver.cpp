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
				{
					std::cout << "Successful Run" << std::endl;
					return true;
				}

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

						//std::cout << "basic flag" << std::endl;

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

						//std::cout << "basic clear" << std::endl;

						curTile->state = TileState::finished;
						if (curTile->field != nullptr)
						{
							curTile->removeAmbigField();
						}
						timeout = false;
						continue;
					}


					

					//more complex cases when ambiguity for one can provide some info for a neighbooring tile

					if (curTile->field == nullptr && curTile->countNearUnknown() - (curTile->value - curTile->countNearFlagged() ) == 1) //one more tile than needed, ambiguous position
					{
						//std::cout << "create ambig at " << curTile->x << ", " << curTile->y << std::endl;
						curTile->createAmbigField();
						timeout = false;
						continue;
					}



					//perform safer operations first that might remove need for complex moves
					if (timeoutCount >= 1)
					{
						//check for surrounding tiles with abiguous fields, then process if anything can be cleared or marked from it
						//check in tiles 2 away for cases where middle unknowns are important
						for (Tile* t1 : curTile->near)
						{
							if (t1 == nullptr)
								continue;

							for (Tile* nearT : t1->near)
							{

								if (nearT != nullptr && nearT->state == TileState::cleared && nearT->field != nullptr)
								{
									nearT->field->update();
									AmbigField* ambField = nearT->field;
									std::vector<Tile*> inField = std::vector<Tile*>(); //tiles in the ambiguity field



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
									//std::cout << "matches: " << matchCount << std::endl;




									if (matchCount == 2 && curTile->countNearUnknown() != 2) //there are more tiles than just in the field
									{
										//if ambiguous segment would complete flagged 
										if (curTile->countNearFlagged() + 1 == curTile->value)
										{
											//std::cout << "before trying to clear around " << curTile->x << ", " << curTile->y << std::endl;
											//board.PrintVisibleBoard();
											for (Tile* t : curTile->near)
											{
												bool isInField = false;
												for (Tile* tF : inField)
												{
													if (t == tF)
														isInField = true;
												}


												if (t != nullptr && !isInField && t->state == TileState::unknown) //if not part of ambigField
												{
													bool check = board.click(t->x, t->y);
													if (!check) //if bomb clicked
													{
														std::cout << "Bomb falsly clicked at " << t->x << ", " << t->y << std::endl;
														ambField->printField();
														return false;
													}

												}
											}

											//std::cout << "ambig clear" << std::endl;

											timeout = false;
											continue;
										}
										else if ((curTile->countNearUnknown() - 1) + curTile->countNearFlagged() == curTile->value && ambField->mineCount == 1) //do not do if 2 could be in 
										{
											//if remaining unknown + already flagged + the ambiguous fill, flag remaining unknown
											for (Tile* t : curTile->near)
											{

												bool isInField = false;
												for (Tile* tF : inField)
												{
													if (t == tF)
														isInField = true;
												}


												//std::cout << "before trying to flag around " << curTile->x << ", " << curTile->y << std::endl;
												//board.PrintVisibleBoard();
												if (t != nullptr && !isInField && t->state == TileState::unknown) //if not part of ambigField
												{
													bool check = board.flag(t->x, t->y);
													if (!check) //if not bomb flagged
													{
														std::cout << "Tile falsly flagged at " << t->x << ", " << t->y << std::endl;
														ambField->printField();
														return false;
													}

												}
											}

											//std::cout << "ambig mark" << std::endl;

											timeout = false;
											continue;

										}


										//Guess between the two ambiguous tiles if failing to find action and nearly timing out
										if (timeoutCount >= 4)
										{
											int choice = rand() % 2;
											Tile* tileChoice = ambField->tiles[choice];

											bool check = board.click(tileChoice->x, tileChoice->y);

											if (!check)
											{
												std::cout << "Incorrect guess clicked at: " << tileChoice->x << ", " << tileChoice->y << std::endl;
												return false;
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

		if (timeoutCount >= 5) //if unable to find anything at all guess randomly
		{
			int randX = rand() % board.height;
			int randY = rand() % board.width;
			while (board.visibleGrid[randX][randY]->state != TileState::unknown)
			{
				randX = rand() % board.height;
				randY = rand() % board.width;
			}

			bool check = board.click(randX, randY);
			if (!check)
			{
				std::cout << "Incorrect random guess made at " << randX << ", " << randY << std::endl;
				return false;
			}

			timeoutCount = 0;
		}
		else if (timeoutCount >= 6) //should not happen hopefully
		{
			std::cout << "Solver timed out, unable to take more steps" << std::endl;
			return false;
		}
	}

	return true;
}

void Solver::CreateBoard(int h, int w, int n)
{
	if (board.height == 0)
		board.~Board();
	board.InitializeBoard(h, w, n);
}

void Solver::ResetBoard()
{
	board.ResetVisibleBoard();
}

void Solver::PrintBoard()
{
	board.PrintVisibleBoard();
}

void Solver::PrintTrueBoard()
{
	board.PrintTrueBoard();
}

Solver::~Solver() {}
