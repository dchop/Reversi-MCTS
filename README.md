# Reversi-MCTS
A command line Reversi game implemented with two AIs: Pure MCTS and MCTS with heuristics

## How to Run
```
# Clean and build executable
$ make
# Run the executable
$ ./bin/game --help
A Reversi game using the MCTS algorithm
Usage:
  ./game [OPTION...]

  -p, --player arg    Choose what algorithm to use to select a move:
                      0-pureMCTS, 1-improvedMCTS, 2-inputPlayer, 3-randomPlayer
                      (default: 0)
  -o, --opponent arg  Choose what algorithm to use to select a move:
                      0-pureMCTS, 1-improvedMCTS, 2-inputPlayer, 3-randomPlayer
                      (default: 1)
  -n, --numgames arg  The number of games to be ran (default: 20)
  -h, --help          Print help and exit
```

## Features
- Both MCTS use [UCT](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Exploration_and_exploitation) to drive selection phase
- Pure MCTS uses random play-outs and returns the move with the most wins
- Improved MCTS uses heuristics to make moves during play-outs and returns the move with the most visits
- Option to play against either AI
- Threading to simulate multiple games in parallel

## Heuristics
- Coin parity
- Captured corners
- Max of the two heuristics above

## Libraries
- [cxxopts](https://github.com/jarro2783/cxxopts)

## Developers
- [Devansh Chopra](https://github.com/dchop)
- [Tyler Trinh](https://github.com/bvtrinh)