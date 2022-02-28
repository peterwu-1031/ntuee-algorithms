# CC and CFLAGS are variables
CC = g++
CFLAGS = -c
# -c option ask g++ to compile the source files, but do not link.


all			: bin/cb

bin/cb			: CycleBreaking.o
				$(CC)  CycleBreaking.o -o bin/cb

CycleBreaking.o	: src/CycleBreaking.cpp
				$(CC) $(CFLAGS) src/CycleBreaking.cpp

# clean all the .o and executable files
clean:
		rm -rf *.o bin/cb
