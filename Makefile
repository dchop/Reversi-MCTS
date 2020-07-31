CPPFLAGS = -std=c++14 -Wall -Wextra -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

all: build

build:
	g++ $(CPPFLAGS) Main.cpp Mcts.cpp Reversi.cpp State.cpp -o game
	
clean:
	rm -f *.o* *.out* game

