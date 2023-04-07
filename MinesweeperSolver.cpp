// MinesweeperSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Solver.h"
#include <iostream>

int main()
{
    Solver solver = Solver();
    bool result = false;
    bool exit = false;

    int height = 16;
    int width = 30;
    int mines = 99;

    while (!exit)
    {
        

        system("cls");
        std::cout << "1: Start solving board with set/default parameters" << std::endl;
        std::cout << "2: Attempt to solve board multiple times and total results" << std::endl;
        std::cout << "3: Set generation parameters" << std::endl;
        std::cout << "4: Exit" << std::endl;
        int input = 0;

        std::cout << std::endl << "Enter an option number to select:   " << std::endl;
        std::cin >> input;
        
        switch (input)
        {
        case 1:
        {
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
        }
            break;
        case 2:
        {
            system("cls");
            int times = 0;
            std::cout << "Enter the number of times to run the board:   ";
            std::cin >> times;

            int successCount = 0;
            int failCount = 0;


            for (int i = 0; i < times; i++)
            {
                solver.CreateBoard(height, width, mines);
                result = solver.Run();
                if (result)
                {
                    successCount++;
                }
                else
                {
                    failCount++;
                }
            }

            std::cout << std::endl << "Successful runs:\t" << successCount << std::endl;
            std::cout << "Failed runs:\t\t" << failCount << std::endl;
            double ratio = (double)successCount / (double)(successCount + failCount) * 100.0;
            std::cout << "Success ratio:\t\t" << ratio << std::endl;

            std::cout << "\n\nEnter 1 to run the same board for " << times << " times or 2 to return to menu : ";
            std::cin >> input;

            while (input == 1)
            {
                successCount = 0;
                failCount = 0;

                for (int i = 0; i < times; i++)
                {
                    solver.CreateBoard(height, width, mines);
                    result = solver.Run();
                    if (result)
                    {
                        successCount++;
                    }
                    else
                    {
                        failCount++;
                    }
                }

                std::cout << std::endl << "Successful runs:\t" << successCount << std::endl;
                std::cout << "Failed runs:\t\t" << failCount << std::endl;
                ratio = (double)successCount / (double)(successCount + failCount) * 100.0;
                std::cout << "Success ratio:\t\t" << ratio << std::endl;


                std::cout << "\n\nEnter 1 to run the same board or 2 to return to menu:   ";
                std::cin >> input;
            }


            
        }
        break;
        case 3:
        {
            system("cls");
            std::cout << "Enter the height of the board:   ";
            std::cin >> height;
            system("cls");
            std::cout << "Enter the width of the board:   ";
            std::cin >> width;
            system("cls");
            std::cout << "Enter the number of mines to place (too dense of a board can crash program) :   ";
            std::cin >> mines;
        }
            break;
        case 4:
            exit = true;
            break;
        default:
            break;
                
        }
    }
}
