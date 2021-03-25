# simple makefile for clang-tidy and compiling
#
# Nirre Pluf 
# 10/7/2020
# CSC 250 Lab 4


# SOURCE = lab4.c
# EXECUTABLE = lab4
# COMPILE_FLAGS = -ansi -pedantic -Wall

# all: $(SOURCE) get_args.c get_args.h
#	gcc $(COMPILE_FLAGS) -o $(EXECUTABLE) $(SOURCE) get_args.c

# tidy: $(SOURCE)
#	clang-tidy -checks='*' $(SOURCE) -- -std=c99

#clean:
#	rm -rf $(EXECUTABLE)
COMPILE_FLAGS = -ansi -pedantic -Wall

lab5: lab5.o get_image_args.o ppm_read_write.o
	gcc -o lab5 lab5.o get_image_args.o ppm_read_write.o

lab5.o: lab5.c get_image_args.h ppm_read_write.h
	gcc -ansi -pedantic -Wall -c lab5.c

ppm_read_write.o: ppm_read_write.h ppm_read_write.c
	gcc -ansi -pedantic -Wall -c ppm_read_write.c

get_image_args.o: get_image_args.h get_image_args.c
	gcc -ansi -pedantic -Wall -c get_image_args.c

tidy: lab5.c
	clang-tidy -checks='*' lab5.c -- -std=c99

clean: 
	\rm -f *.o lab5


