set LCC=c:\lcc
cd source\windows
set PATH=%LCC%\bin;%PATH%
make -f Makefile.lcc clean
cd ..\..
del putty.exe
