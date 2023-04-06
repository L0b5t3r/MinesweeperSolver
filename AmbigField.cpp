#include "AmbigField.h"
#include "Tile.h"
#include <iostream>

AmbigField::AmbigField()
{
	count = 0;
	tiles = std::vector<Tile*>();
	mineCount = 0;
}


int AmbigField::getMinesLeftCount()
{
	int count = 0;
	for (Tile* t : tiles)
	{
		if (t->state == TileState::marked)
		{
			count++;
		}
	}
	

	return mineCount - count; //incase tiles were flagged in meantime
}

void AmbigField::update()
{
	std::vector<Tile*> newTiles = std::vector<Tile*>();
	for (Tile* t : tiles)
	{
		if (t != nullptr && t->state == TileState::unknown)
		{
			newTiles.push_back(t);
		}
		else if (t != nullptr && t->state == TileState::marked)
		{
			mineCount--;
		}
	}
	count = newTiles.size();
	tiles = newTiles;
}

void AmbigField::printField()
{
	std::cout << "Faulting Ambig field, containing " << getMinesLeftCount() << " mines\n";
	for (Tile* t : tiles)
	{
		if (t != nullptr)
		{
			std::cout << t->x << ", " << t->y << std::endl;
		}
	}
}

AmbigField::~AmbigField()
{
}