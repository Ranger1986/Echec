# A simple makefile for compiling a C++ project

.DEFAULT_GOAL := all

# Define the targets
# target template = exe/.out
TARGETS :=  exe/main.out

# Define the source files corresponding to each target
# sources template = src/.cpp
SOURCES := src/main.cpp

# Rule to compile each source file into its corresponding target
$(TARGETS): exe/%.out: src/%.cpp
	g++ -o $@ $< -Wall

all: clean $(TARGETS)

clean: 
	rm -rf exe/*.out
	
test: $(TARGETS)
	./exe/main.out