set PATH=c:\lcc\bin;%PATH%
cd source\windows
make -f Makefile.lcc COMPAT="-DNO_MULTIMON -DNO_IPV6 -g2" VER="-DRELEASE=0.60.T24.DEBUG" putty.exe
copy putty.exe ..\..\putty_t24.exe

