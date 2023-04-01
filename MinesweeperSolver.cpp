// MinesweeperSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Solver.h"
#include <iostream>

int main()
{
    Solver solver = Solver();
    bool result = false;

    solver.CreateBoard(10, 10, 20);

    result = solver.Run();
    solver.PrintBoard();
}
