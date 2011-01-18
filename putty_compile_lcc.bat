set LCC=c:\lcc
cd source\windows
set PATH=%LCC%\bin;%PATH%
set INCLUDE=%LCC%\include;%INCLUDE%
set LIB=%LCC%\lib;%LIB
make -f Makefile.lcc COMPAT="-DNO_MULTIMON -DNO_IPV6" VER="-DRELEASE=0.60.T24.02" putty.exe
copy putty.exe ..\..

