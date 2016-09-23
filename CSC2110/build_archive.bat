@echo off
cls

set THE_PATH=%1:
::set path=%THE_PATH%\MinGW\bin;%THE_PATH%\MinGW\msys\1.0\bin;c:\Windows

g++ -c String.cpp
g++ -c Tokens.cpp
g++ -c ReadFile.cpp
g++ -c WriteFile.cpp
g++ -c Keyboard.cpp
g++ -c Random.cpp
g++ -c Matrix.cpp
g++ -c Poly.cpp
g++ -c CD.cpp
g++ -c Song.cpp
g++ -c Matrix.cpp
g++ -c Integer.cpp
g++ -c Double.cpp
g++ -c HighPerformanceCounter.cpp
g++ -c Permutation.cpp

ar -r libCSC2110.a *.o






