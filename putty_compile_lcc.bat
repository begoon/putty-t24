rem turn optimization off!
cd source\windows
set INCLUDE=C:\kzm\tools\lcc\include;%INCLUDE%
set PATH=C:\kzm\tools\lcc\bin;%PATH%
set LIB=C:\kzm\tools\lcc\lib;%LIB
make 2>ERR.TXT
