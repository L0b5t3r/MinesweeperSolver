const ffi = require('ffi-napi');

export const solver = ffi.Library('x64\Debug\MinesweeperSolver.dll', {
   'generateBoard' : ['void', ['int', 'int', 'int']],
   'runSolver' : ['string', []]
});