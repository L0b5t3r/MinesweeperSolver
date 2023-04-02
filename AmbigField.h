#pragma once
#include <vector>

class Tile;  //forward declaration to avoid circular dependency

class AmbigField //when a tile has has value - 1 unknown tiles, create field of those tiles to perform more complex steps
{
	private:

	public:
		int count;

		std::vector<Tile*> tiles;

		AmbigField();
		~AmbigField();

};

