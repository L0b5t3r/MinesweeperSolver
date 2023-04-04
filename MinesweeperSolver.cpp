// MinesweeperSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Solver.h"
#include <iostream>

int main()
{
    Solver solver = Solver();
    bool result = false;
    bool exit = false;

    int height = 10;
    int width = 10;
    int mines = 15;

    while (!exit)
    {
        

        system("cls");
        std::cout << "1: Start solving board with set/default parameters" << std::endl;
        std::cout << "2: Set generation parameters" << std::endl;
        std::cout << "3: Exit" << std::endl;
        int input = 0;

        std::cout << std::endl << "Enter an option number to select:   " << std::endl;
        std::cin >> input;
        
        switch (input)
        {
        case 1:
            system("cls");
            solver.CreateBoard(height, width, mines);
            result = solver.Run();
            solver.PrintBoard();
            if (result)
            {
                std::cout << "Solver successfully cleared board" << std::endl;
            }
            else
            {
                std::cout << "Solver was unsuccessfull" << std::endl;
            }

            std::cout << "\n\nEnter 1 to run the same board or 2 to return to menu:   ";
            std::cin >> input;

            while (input == 1)
            {
                system("cls");
                solver.ResetBoard();
                result = solver.Run();
                solver.PrintBoard();
                if (result)
                {
                    std::cout << "Solver successfully cleared board" << std::endl;
                }
                else
                {
                    std::cout << "Solver was unsuccessfull" << std::endl;
                }

                std::cout << "\n\nEnter 1 to run the same board or 2 to return to menu:   ";
                std::cin >> input;
            }

            break;
        case 2:
            system("cls");
            std::cout << "Enter the height of the board:   ";
            std::cin >> height;
            system("cls");
            std::cout << "Enter the width of the board:   ";
            std::cin >> width;
            system("cls");
            std::cout << "Enter the number of mines to place (too dense of a board can crash program) :   ";
            std::cin >> mines;
            break;
        case 3:
            exit = true;
            break;
        default:
            break;
                
        }
    }
}
