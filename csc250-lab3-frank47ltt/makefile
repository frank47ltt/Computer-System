# simple makefile for clang-tidy and compiling
#
# Nirre Pluf 
# 9/26/2020
# CSC 250 Lab 3

SOURCE = lab3.c
EXECUTABLE = lab3
COMPILE_FLAGS = -ansi -pedantic -Wall -g

all: tidy
	gcc $(COMPILE_FLAGS) -o $(EXECUTABLE) $(SOURCE)

tidy: $(SOURCE)
	clang-tidy -checks='*' $(SOURCE) -- -std=c99

clean:
	rm -rf $(EXECUTABLE)

