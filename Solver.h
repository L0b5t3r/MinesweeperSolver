#pragma once
#include "Board.h"
#include "AmbigField.h"
#include <iostream>

class Solver
{
	private:


	public:
		Board board;

		Solver();
		Solver(Board b);
		~Solver();

		bool Run();

		void CreateBoard(int h, int w, int n);
		void PrintBoard();
};

