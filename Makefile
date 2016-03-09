# Evan Hsia, ehsia1, Homework 3 Makefile

# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# Compiles catalog.c into an object file
catalog.o: catalog.c hw3.h
	$(CC) $(CFLAGS) -c catalog.c

#Compiles transcript.c into object file
transcript.o: transcript.c hw3.h
	$(CC) $(CFLAGS) -c transcript.c

# Compiles test_hw3.c into an object file
test_hw3.o: test_hw3.c hw3.h
	$(CC) $(CFLAGS) -c test_hw3.c

#Compiles hw2.c into an object file
hw3.o: hw3.c hw3.h
	$(CC) $(CFLAGS) -c hw3.c

# Links the test_hw3 executable
test_hw3: test_hw3.o catalog.o transcript.o
	$(CC) -o test_hw3 test_hw3.o catalog.o transcript.o

#Links the hw3 executable
hw3: hw3.o catalog.o transcript.o
	$(CC) -o hw3 hw3.o catalog.o transcript.o

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o test_hw3 hw3 *.gcov

