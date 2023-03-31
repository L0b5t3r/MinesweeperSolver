#pragma once
enum TileState
{
	unknown = 1, //tile not checked yet
	cleared = 2, //tile checked but still has unknown surrounding tiles
	marked = 3,  //tile marked as bomb, can be chosen incorrectly
	finished = 4   //tile cleared and all surrounding tiles cleared
};

#pragma once
#include <vector>
class Tile
{
	private:


	public:
		Tile();
		Tile(int v);
		~Tile();

		int value;
		TileState state;

		Tile* up;
		Tile* upRight;
		Tile* right;
		Tile* downRight;
		Tile* down;
		Tile* downLeft;
		Tile* left;
		Tile* upLeft;

		std::vector<Tile*> near;


		int countNearMines();

		void updateNearTiles();
};



