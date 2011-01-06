set LCC=c:\lcc
set PATH=%LCC%\bin;%PATH%
set INCLUDE=%LCC%\include;%INCLUDE%
set LIB=%LCC%\lib;%LIB
cd source\windows
make -f Makefile.lcc "COMPAT=-DNO_IPV6 -DNO_MULTIMON" putty.exe && copy *.exe ..\..
