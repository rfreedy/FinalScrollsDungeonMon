all: main.o fsdmgame.o fsdmlevel.o Tile.o Dot.o LTexture.o entity.o character.o enemy.o
	g++ main.o fsdmgame.o fsdmlevel.o Tile.o Dot.o LTexture.o entity.o character.o enemy.o -w -lSDL2 -lSDL2_image -o FSDM

main.o: main.cpp
	g++ -c main.cpp
fsdmgame.o: fsdmgame.cpp
	g++ -c fsdmgame.cpp
fsdmlevel.o: fsdmlevel.cpp
	g++ -c fsdmlevel.cpp
Tile.o: Tile.cpp
	g++ -c Tile.cpp
Dot.o: Dot.cpp
	g++ -c Dot.cpp
LTexture.o: LTexture.cpp
	g++ -c LTexture.cpp
entity.o: entity.cpp
	g++ -c entity.cpp
character.o: character.cpp
	g++ -c character.cpp
enemy.o: enemy.cpp
	g++ -c enemy.cpp

clean:
	rm *.o FSDM
