@echo off
cls

g++ -I.\CSC2110 -c SortedListArrayDriver.cpp
g++ -g -L.\CSC2110 -o SortedListArray.exe SortedListArrayDriver.o -lCSC2110
