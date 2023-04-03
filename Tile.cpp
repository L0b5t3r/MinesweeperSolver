#include "Tile.h"
#include "AmbigField.h"

Tile::Tile()
{
	value = 0;
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
	state = TileState::unknown;
	x = y = 0;
}

Tile::~Tile()
{}

Tile::Tile(int x, int y)
{
	value = 0;
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
	state = TileState::unknown;
	this->x = x;
	this->y = y;
}

Tile::Tile(int x, int y, int v)
{
	value = v;
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
	state = TileState::unknown;
	this->x = x;
	this->y = y;
}


int Tile::countNearMines() //count actual mines from true board
{
	int count = 0;
	for (Tile* t : near)
	{
		if (t != nullptr && t->value == -1)
			count++;
	}
	return count;
}

int Tile::countNearFlagged() //count flagged tiles from visible board
{
	int count = 0;
	for (Tile* t : near)
	{
		if (t != nullptr && t->state == TileState::marked)
			count++;
	}
	return count;
}

int Tile::countNearUnknown() //count unknown tiles from visible board
{
	int count = 0;
	for (Tile* t : near)
	{
		if (t != nullptr && t->state == TileState::unknown)
			count++;
	}
	return count;
}


void Tile::createAmbigField()
{
	field = new AmbigField();

	for (Tile* t : near)
	{
		if (t != nullptr && t->state == TileState::unknown) //add unknown tiles to Ambig field
		{
			field->tiles.push_back(t);
		}
	}
	field->count = field->tiles.size();
	field->mineCount = value - countNearFlagged();
}

void Tile::removeAmbigField() 
{
	delete field;
	field = nullptr;
}


void Tile::updateNearTiles()
{
	near = { up, upRight, right, downRight, down, downLeft, left, upLeft };
}