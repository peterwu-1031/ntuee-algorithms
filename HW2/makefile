# CC and CFLAGS are variables
CC = g++
CFLAGS = -c
# -c option ask g++ to compile the source files, but do not link.


all			: bin/mps

bin/mps			: maxPlanarSubset.o 
				$(CC)  maxPlanarSubset.o -o bin/mps

maxPlanarSubset.o	: src/maxPlanarSubset.cpp
				$(CC) $(CFLAGS) src/maxPlanarSubset.cpp

# clean all the .o and executable files
clean:
		rm -rf *.o bin/mps
