putty for T24 project
=====================

![](https://raw.github.com/begoon/putty-t24/master/doc/putty-t24.png)

Build
-----

To build you need the `lcc.exe` compiler installed into the `c:\lcc` directory.

http://www.cs.virginia.edu/~lcc-win32/

Also `Makefile` requires GNU Make, which can be downloaded from
http://sourceforge.net/projects/unxutils/. You only need `make.exe` file from
that package.

Finally, before the build you need to add `c:\lcc\bin` into your PATH (`lcc.exe`
and `lcclnk.exe` should work without using absolute paths).

It is convinient to install GitHub for Windows because it provides the latest
version of git, plus a few UNIX tools like "rm".

Compilation:

    make

It will produce a file called `putty-t24.exe`.

Packaging
---------

    make zip

It will produce an archive called `putty-t24.7z` containing the executable
and CHANGES.txt.
