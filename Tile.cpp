#include "Tile.h"

Tile::Tile()
{
	value = 0;
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
	state = TileState::unknown;
}

Tile::~Tile()
{}

Tile::Tile(int v)
{
	value = v;
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
	state = TileState::unknown;
}


int Tile::countNearMines()
{
	int count = 0;
	for (Tile* t : near)
	{
		if (t != nullptr && t->value == -1)
			count++;
	}
	return count;
}

void Tile::updateNearTiles()
{
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
}