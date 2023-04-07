#pragma once
#include "Tile.h"
#include <vector>
class Board
{
	private:
		
		void setNearTiles(int i, int o);

	public:
		Board();
		~Board();

		int totalMines;
		int remainingMines;
		int height, width;

		std::vector<std::vector<Tile*>> visibleGrid; //discovered tiles 
		std::vector<std::vector<Tile*>> trueGrid; //true value of each tile, unknown to solver

		void InitializeBoard(int h, int w, int n);
		void ResetVisibleBoard();

		bool click(int x, int y);
		bool flag(int x, int y);

		void clear0s(int x, int y);

		void PrintTrueBoard();
		void PrintVisibleBoard();

		void PrintFailDebug(int x, int y);

};

