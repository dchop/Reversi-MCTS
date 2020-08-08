CPPFLAGS = -std=c++14 -Wall -Wextra -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

all: clean build run

build:
	g++ $(CPPFLAGS) Main.cpp Reversi.cpp State.cpp Node.cpp -o game

run:
	./game
	
clean:
	rm -f *.o* *.out* game

mem: clean build mem-check

mem-check:
	valgrind --leak-check=full ./game

