#include "AmbigField.h"
#include "Tile.h"

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
			count++;
	}
	return count;

	return mineCount - count; //incase tiles were flagged in meantime
}


AmbigField::~AmbigField()
{
}