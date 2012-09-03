.PHONY: test

INCLUDE=-Isource -Isource/windows -Itest/cmockery

all: test build release

TEST_SRC = \
  test\unittest_runner.c \
  test\cmockery\cmockery.c \
  source\misc.c \
  source\t24.c

TEST_OBJ = $(subst .c,.obj,$(TEST_SRC))

test:
	lcc -p6 -D_WINDOWS $(INCLUDE) test/unittest_runner.c
	lcc -p6 -D_WINDOWS $(INCLUDE) test/cmockery/cmockery.c
	lcc -p6 -D_WINDOWS $(INCLUDE) source/misc.c
	lcc -p6 -D_WINDOWS $(INCLUDE) source/t24.c
	lcclnk -o unittest_runner.exe $(TEST_OBJ)
	unittest_runner.exe 

build:
	cd source/windows && \
	$(MAKE) -f Makefile.lcc \
		COMPAT="-DNO_MULTIMON -DNO_IPV6" \
		VER="-DRELEASE=0.60.T24.07.4" \
		putty.exe

build-debug:
	cd source/windows && \
	$(MAKE) -f Makefile.lcc PATH=$(LCC) \
		COMPAT="-DNO_MULTIMON -DNO_IPV6 -g2" \
		VER="-DRELEASE=0.60.T24.07.DEBUG" \
		putty.exe

release:
	cp source/windows/putty.exe putty-t24.exe

clean:
	-(cd source/windows/ && rm *.obj *.exe *.res)
	-rm $(TEST_OBJ)
	-rm unittest_runner.exe putty.exe

zip:
	7z a -r -mx9 putty-t24.7z putty_t24.exe CHANGES.txt
