# This file is used to make executable on ubuntu platform.

CC=g++
GFLAGS= -o main.out -std=g++11

make: clean
	$(CC) $(GFLAGS) main.cpp

clean:
ifneq ("$(wildcard ./main.out)", "")
	rm make.out
endif