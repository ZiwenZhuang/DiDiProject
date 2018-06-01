# This file is used to make executable on ubuntu platform.

CC=g++
GFLAGS= -o main.out -std=c++11
PFLAGS= -std=c++11
make: clean
	$(CC) $(GFLAGS) main.cpp utilities/*.cpp included/*.cpp
	 
pixel: pixel.cpp
	$(CC) $(PFLAGS) -o pixel pixel.cpp
clean:
ifneq ("$(wildcard ./main.out)", "")
	rm main.out
endif
