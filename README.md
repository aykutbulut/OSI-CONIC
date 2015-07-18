OSI-CONIC
===
[![Build Status](https://travis-ci.org/aykutbulut/OSI-CONIC.svg?branch=master)](https://travis-ci.org/aykutbulut/OSI-CONIC)
!https://travis-ci.org/aykutbulut/OSI-CONIC.svg?branch=master!:https://travis-ci.org/aykutbulut/OSI-CONIC
{<img src="https://travis-ci.org/aykutbulut/OSI-CONIC.svg?branch=master" alt="Build Status" />}[https://travis-ci.org/aykutbulut/OSI-CONIC]
.. image:: https://travis-ci.org/aykutbulut/OSI-CONIC.svg?branch=master
    :target: https://travis-ci.org/aykutbulut/OSI-CONIC
=for HTML <a href="https://travis-ci.org/aykutbulut/OSI-CONIC"><img src="https://travis-ci.org/aykutbulut/OSI-CONIC.svg?branch=master"></a>
#https://api.travis-ci.org/repos/aykutbulut/OSI-CONIC/cc.xml?branch=master



Conic problem solver interface library. Extends Coin-OR's OSI interface to conic problems. Inherits Coin-OR's OsiCLpSolverInterface class and adds conic problem specific methods (querring cones, etc.).

Dependencies
===
Depends Osi and CoinUtils.

Install
===
After pulling OsiConic, run the following commands.<br />
cd OsiConic <br />
./get_dependencies.sh <br />
./compile.sh <br />
get_dependencies.sh will download Osi and CoinUtils. compile.sh will compile dependencies and OsiConic and it will install dependency libraries and OsiConic library to OsiConic/build/lib. Header files will be installed to OsiConic/build/include/coin. Pkg-config .pc files will be installed to OsiConic/build/lib/pkgconfig.

