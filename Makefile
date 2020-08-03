CPPFLAGS = -std=c++14 -Wall -Wextra -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

all: clean build run

build:
	g++ $(CPPFLAGS) Main.cpp Mcts.cpp Reversi.cpp State.cpp -o game

run:
	./game
	
clean:
	rm -f *.o* *.out* game

