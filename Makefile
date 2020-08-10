CPPFLAGS = -std=c++14 -Wall -Wextra -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g
LIB = -pthread
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)
INC = -I include
BIN = bin/game

all: clean build run

build:
	g++ $(CPPFLAGS) $(LIB) $(SRC) $(INC) -o $(BIN)

run:
	./$(BIN)
	
clean:
	rm -f *.o* *.out* $(BIN)

mem: clean build mem-check

mem-check:
	valgrind --leak-check=full ./$(BIN)