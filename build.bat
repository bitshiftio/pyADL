@echo off
rem Set these values according to where you installed the software
set SDK=D:\WinDDK\
set NET=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\
set ADL=D:\Opt\ADL\

Set PATH=%NET%;%PATH%
set INCLUDE=%NET%\include;%ADL%\include;%INCLUDE%
set LIB=%NET%\lib;%LIB%

echo %PATH%
setup.py install build

pause