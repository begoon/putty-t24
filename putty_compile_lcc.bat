set PATH=c:\lcc\bin;%PATH%
cd source\windows
make -f Makefile.lcc COMPAT="-DNO_MULTIMON -DNO_IPV6" VER="-DRELEASE=0.60.T24.02" putty.exe
copy putty.exe ..\..

