OSI-CONIC [![Build Status](https://travis-ci.org/aykutbulut/OSI-CONIC.svg?branch=master)](https://travis-ci.org/aykutbulut/OSI-CONIC)
===


Conic problem solver interface library. Extends Coin-OR's OSI interface to conic problems. Inherits Coin-OR's OsiCLpSolverInterface class and adds conic problem specific methods (querying cones, etc.).

Dependencies
===
Depends Osi and CoinUtils.

Install
===

Easy Install
----
After cloning OsiConic, go to the directory containing it and run the following commands.
```{r, engine='bash', count_lines}
git clone https://gist.github.com/tkralphs/13d4529b4d4e8889f3a6 scripts
bash scripts/get.dependencies.sh fetch
bash scripts/get.dependencies.sh build --quiet
```
First command clones a script to fetch dependencies and build them along OsiConic. Second command fetches dependencies listed in Dependencies file. Third command builds OsiConic and its dependencies. Third command will install dependency libraries and OsiConic library to OSI-CONIC/lib. Header files will be installed to OSI-CONIC/include/coin. Pkg-config .pc files will be installed to OSI-CONIC/lib/pkgconfig.

Instructions for advanced users
----
If you have all dependencies installed you can link them through pkg-config. Just put the .pc files of the dependencies to your PKG_CONFIG_PATH environment variable. After that ```{r, engine='bash'} ./configure && make install``` should work.

If you are installing OSI-CONIC to the same directory that already has dependencies installed, configure will locate the Dependencies.
