import {solver} from './solverLib.js';

function solveBoard()
{
   let height = Number((<HTMLInputElement>document.getElementById("height"))!.value);
   let width = Number((<HTMLInputElement>document.getElementById("width"))!.value);
   let numMines = Number((<HTMLInputElement>document.getElementById("numMines")!).value);
   
   solver.generateBoard(height, width, numMines);
   
   let result = solver.runSolver();
   
   const table = <HTMLTableElement>document.getElementById("resultTable")!;
   
   table.innerHTML = ""; // Clear previous table contents
   
   for (let i = 0; i < height; i++) {
      const row = table.insertRow();
      for (let j = 0; j < width; j++) {
         const cell = row.insertCell();
         cell.innerHTML = result[i*width+j];
      }
   }
}