#pragma once
#include "Board.h"
#include "AmbigField.h"
#include <iostream>

class Solver
{
	private:
		Board board;

	public:
		

		Solver();
		Solver(Board b);
		~Solver();

		bool Run();

		void CreateBoard(int h, int w, int n);
		void ResetBoard();
		void PrintBoard();
};

