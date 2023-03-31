#include "Solver.h"

Solver::Solver()
{
	Board board();
}


void Solver::Run()
{

}

void Solver::CreateBoard(int h, int w, int n)
{
	board.InitializeBoard(h, w, n);
	board.PrintTrueBoard();
}


Solver::~Solver() {}
