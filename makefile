all: 04_key_presses.cpp
	g++ 04_key_presses.cpp -w -lSDL2 -o 04_key_presses

clean:
	rm *.o 04_key_presses
