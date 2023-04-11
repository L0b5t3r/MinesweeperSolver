#include "Solver.h"

#ifdef _cplusplus //ensure same runtime lib
extern "C++" {
#endif

Solver solver = Solver();

extern "C" _declspec(dllexport)
void generateBoard(int h, int w, int n)
{
	solver.CreateBoard(h, w, n);
}

extern "C" _declspec(dllexport)
std::string runSolver()
{
	solver.Run();
	return solver.GetVisibleBoard();
}

#ifdef _cplusplus
}
#endif