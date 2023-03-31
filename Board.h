#pragma once
#include "Tile.h"
#include <vector>
class Board
{
	private:
		int height, width;


	public:
		Board();
		~Board();

		int totalMines;
		int remainingMines;

		std::vector<std::vector<Tile*>> visibleGrid; //discovered tiles 
		std::vector<std::vector<Tile*>> trueGrid; //true value of each tile, unknown to solver

		void InitializeBoard(int h, int w, int n);

		void PrintTrueBoard();
		void PrintVisibleBoard();

};

