combatTest: combatTest.o entity.o character.o enemy.o
	g++ combatTest.o entity.o character.o enemy.o -lSDL2 -lSDL2_image -o combatTest

combatTest.o: combatTest.cpp
	g++ -c combatTest.cpp

entity.o: entity.cpp
	g++ -c entity.cpp

character.o: character.cpp
	g++ -c character.cpp

enemy.o: enemy.cpp
	g++ -c enemy.cpp
