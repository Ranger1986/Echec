# A simple makefile for compiling a C++ project

.DEFAULT_GOAL := all

all:
	g++ -o exe/main.out src/main.cpp src/Piece.cpp src/Board.cpp -Wall
	./exe/main.out