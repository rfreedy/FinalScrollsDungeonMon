CC=g++

TARGETS=fsdm

DBGFLAGS=-O0 -g3

all: $(TARGETS)

fsdm: fsdmrender.cpp
	$(CC) fsdmrender.cpp -w -lSDL2 -lSDL2_image -o fsdm

debug: fsdmrender.cpp
	$(CC) fsdmrender.cpp $(DBGFLAGS) -lSDL2 -lSDL2_image -o fsdm
