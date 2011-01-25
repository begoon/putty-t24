set PATH=c:\lcc\bin;%PATH%
del *.obj
lcc -p6 -Itest\cmockery test\cmockery\cmockery.c && ^
lcc -p6 -Itest\cmockery test\unittest_runner.c && ^
lcclnk -o unittest_runner.exe unittest_runner.obj cmockery.obj && ^
unittest_runner.exe

