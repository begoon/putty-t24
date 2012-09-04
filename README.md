PUTTY for T24 project
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


Crash course
============

Search
------

Search can be used only inside T24 - normally at "AWAITING PAGE 
INSTRUCTIONS" prompt. Use F8 to input search string, F9 to search 
forward, F10 to search backwards. If target string wasn't found at the 
current page, next page appears (or previous for backward search). When 
one (or more) matches found, search is stopped. It means that you can 
press and hold F9 or F10 until you see all matches on particular page 
being highlighted or until the last (or first) page is shown. 

If the search was successful and therefore stoped but you want to 
continue, press F2 or F3 (depending on search direction) and then F9 or 
F10 again. 

You can search not only words or words' fragments - search anything that 
is shown on the screen so you can try something like: `BOEINGGBP 
Corporate| Current Ac` (unfortunately no longer than that): 

![](https://raw.github.com/begoon/putty-t24/master/doc/search/sample1.jpg)

Search looks for data only inside normal T24 Classic bounds (lines 4 to 
19 inclusive) so it will not find `BOEINGCHF` in the bottom of the 
following screen: 

![](https://raw.github.com/begoon/putty-t24/master/doc/search/sample2.jpg)

... It's a good idea to correct some default enquiries since it looks 
that Model Bank staff don't care about T24 Classic anymore. 

Known issues: national characters (umlauts etc) will not be found.

JED code highighting
--------------------

There's no intention to replace any existing T24 development tool like 
Toolbox - consider it as a helper that might be useful for quick 
development, code analysis, working in non-T24 environment. You can 
consider it as "augmented" JED. No changes to JED itself - everything is 
done at Putty level. Depending on what you have on the screen, an 
attempt is made to highlight jBC code. Of course, if the line of code 
goes beyond the screen, Putty has no way to know how to highlight it all 
so the highlighting may be changing as you browse the screen back and 
forth. 

Highlighting might be a bit slow depending on the amount of text shown 
on the screen. 

There might be some highlighting when PuTTY thinks it's in JED:

![](https://raw.github.com/begoon/putty-t24/master/doc/search/sample3.jpg)

If it annoys you, use F12 to toggle highlighting on/off.

**Note**: this version of PuTTY uses the different registry key than initial one:  `HKEY\_CURRENT\_USER\Software\SimonTatham\PuTTY\_T24\`.

If you rename your older registry key in the registry in order to be 
used in this version, it's not guaranteed that it will work. 
