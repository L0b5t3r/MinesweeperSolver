#pragma once
#include "Board.h"
class Solver
{
	private:


	public:
		Board board;

		Solver();
		Solver(Board b);
		~Solver();

		void Run();

		void CreateBoard(int h, int w, int n);

};

