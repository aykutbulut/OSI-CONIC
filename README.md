OSI-CONIC
=========
Conic problem solver interface library. Extends Coin-OR's OSI interface to conic problems. Inherits Coin-OR's OsiCLpSolverInterface class and adds conic problem specific methods (querring cones, etc.).

Dependencies
=========
Depends Osi and CoinUtils.

Install
=========
After pulling OsiConic, run the following commands.\\
cd OsiConic\\
./get_dependencies\\
./compile.sh\\
get_dependencies.sh will download Osi and CoinUtils. compile.sh will compile dependencies and OsiConic and it will install dependency libraries and OsiConic library to OsiConic/build/lib. Header files will be installed to OsiConic/build/include/coin. Pkg-config .pc files will be installed to OsiConic/build/lib/pkgconfig.

