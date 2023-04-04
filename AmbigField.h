#pragma once
#include <vector>

class Tile;  //forward declaration to avoid circular dependency

//at LEAST 1 in field
class AmbigField //when a tile has has value - 1 unknown tiles, create field of those tiles to perform more complex operations
{
	private:

	public:
		int count;
		int mineCount;

		std::vector<Tile*> tiles;

		AmbigField();
		~AmbigField();

		int getMinesLeftCount();
};

