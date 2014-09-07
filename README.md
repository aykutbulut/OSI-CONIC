OSI-CONIC
=========
Conic problem solver interface library. Extends Coin-OR's OSI interface to conic problems. Inherits Coin-OR's OsiCLpSolverInterface class and adds conic problem specific methods (querring cones, etc.).

Dependencies
=========
Depends Osi-Clp, Osi and CoinUtils. Locates them using pkg-config.

Install
=========
../configure && make && make install should work if dependencies are in users PKG_CONFIG_PATH.
