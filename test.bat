set PATH=c:\lcc\bin;%PATH%
del *.obj
set INCLUDE=-Isource -Isource\windows -Itest\cmockery
lcc -p6 -D_WINDOWS %INCLUDE% test\cmockery\cmockery.c && ^
lcc -p6 -D_WINDOWS %INCLUDE% test\unittest_runner.c && ^
lcc -p6 -D_WINDOWS %INCLUDE% source\misc.c && ^
lcc -p6 -D_WINDOWS %INCLUDE% source\t24.c && ^
lcclnk -o unittest_runner.exe unittest_runner.obj cmockery.obj misc.obj t24.obj && ^
unittest_runner.exe && ^
del *.obj unittest_runner.exe

