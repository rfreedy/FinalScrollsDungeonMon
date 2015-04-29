all: main.o fsdmgame.o fsdmlevel.o Tile.o LTexture.o entity.o character.o enemy.o
	g++ -O0 -g3 main.o fsdmgame.o fsdmlevel.o Tile.o LTexture.o entity.o character.o enemy.o -w -lSDL2 -lSDL2_image -lSDL2_ttf -o FSDM

main.o: main.cpp
	g++ -O0 -g3 -c main.cpp
fsdmgame.o: fsdmgame.cpp
	g++ -O0 -g3 -c fsdmgame.cpp
fsdmlevel.o: fsdmlevel.cpp
	g++ -O0 -g3 -c fsdmlevel.cpp
Tile.o: Tile.cpp
	g++ -O0 -g3 -c Tile.cpp
LTexture.o: LTexture.cpp
	g++ -O0 -g3 -c LTexture.cpp
entity.o: entity.cpp
	g++ -O0 -g3 -c entity.cpp
character.o: character.cpp
	g++ -O0 -g3 -c character.cpp
enemy.o: enemy.cpp
	g++ -O0 -g3 -c enemy.cpp

clean:
	rm *.o FSDM
