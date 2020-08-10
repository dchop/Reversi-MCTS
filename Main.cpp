#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include "cxxopts.h"
#include "Player.h"

using namespace std;

// Play a game of Reversi
void startGame(vector<tuple<char, int, int, int, double>> &results, int index, int p1Type, 
    int p2Type, bool display=false) {
    srand(time(0));

    Player p1 = Player('T', p1Type);
    Player p2 = Player('F', p2Type);
    State *state = new State();
    Reversi game;
    Move move1;
    Move move2;
    vector<Move> moves1 = game.listMoves(state->getState(), 'T', 'F');
    vector<Move> moves2 = game.listMoves(state->getState(), 'F', 'T');

    if (display)
        game.printBoard(state->getState());

    auto start = chrono::high_resolution_clock::now();
    while (true) {

        if (moves1.size() > 0) {
            move1 = p1.getMove(game, state, moves1);
            game.makeMove(state, move1);
        }
        state->togglePlayer();

        if (display)
            game.printBoard(state->getState());

        // Check if game is over
        moves1 = game.listMoves(state->getState(), p1.player, p2.player);
        moves2 = game.listMoves(state->getState(), p2.player, p1.player);
        if (game.checkWin(state->getState(), moves1.size(), moves2.size()))
            break;

        if (moves2.size() > 0) {
            move2 = p2.getMove(game, state, moves2);
            game.makeMove(state, move2);
        }

        state->togglePlayer();

        if (display)
            game.printBoard(state->getState());

        // Check if game is over
        moves1 = game.listMoves(state->getState(), p1.player, p2.player);
        moves2 = game.listMoves(state->getState(), p2.player, p1.player);
        if (game.checkWin(state->getState(), moves1.size(), moves2.size()))
            break;
    }
    auto end = chrono::high_resolution_clock::now();
    double totalTime = chrono::duration_cast<chrono::duration<double>>(end - start).count();

    int white, black;
    tie(white, black) = game.score(state->getState());
    results[index] = make_tuple(game.winningPlayer(state->getState()), white, black, 
        state->getIterations(), totalTime);
    delete state;
}

// Display the winner, score, number of iterations used in MCTS, length of game (s)
void displayResults(vector<tuple<char, int, int, int, double>> results, double time) {

    char winner;
    int wWins = 0;
    int bWins = 0;

    printf("WINNER\t\tSCORE(W-B)\t\tITERATIONS\t\tTIME\n");
    for (auto &res:results) {
        winner = get<0>(res);
        if (winner == 'T')
            wWins += 1;
        else if (winner == 'F')
            bWins += 1;

        printf("%c\t\t\t%d-%d\t\t%d\t\t%f\n", winner, get<1>(res), get<2>(res), get<3>(res),
            get<4>(res));
    }

    printf("Player1Wins: %d\t\t Player2Wins: %d\n", wWins, bWins);
    std::cout << "Total Time: " << time << "s\n";
}

// Use threading to simulate multiple games 
void simulateGames(int const numGames, int p1, int p2, bool display) {

    vector<thread> threads;
    vector<tuple<char, int, int, int, double>> results(numGames);

    auto start = chrono::high_resolution_clock::now();

    printf("Playing %d games\n", numGames);
    for (int i = 0; i < numGames; i++)
        threads.push_back(thread(startGame, ref(results), i, p1, p2, display));

    for (auto &t:threads) {
        if (t.joinable())
            t.join();
    }
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::duration<double>>(end - start).count();

    displayResults(results, duration);
}

int main(int argc, char* argv[]) {

    // Parse commandline arguments
    cxxopts::Options options("./game", "A Reversi game using the MCTS algorithm");
    options.add_options()
        ("p,player", "Choose what algorithm to use to select a move: 0-pureMCTS, 1-improvedMCTS,"
            "2-inputPlayer, 3-randomPlayer", cxxopts::value<int>()->default_value("3"))
        ("o,opponent", "Choose what algorithm to use to select a move: 0-pureMCTS, 1-improvedMCTS,"
            "2-inputPlayer, 3-randomPlayer", cxxopts::value<int>()->default_value("0"))
        ("n,numgames", "The number of games to be ran", cxxopts::value<int>()->
            default_value("50"))
        ("h,help","Print help and exit")
        ;
    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help({"", "p1", "p2","n","h"}) << std::endl;
      exit(0);
    }

    int p1Type = result["p"].as<int>();
    int p2Type = result["o"].as<int>();
    int numGames = (p1Type == 2 || p2Type == 2) ? 1 : result["n"].as<int>();
    bool displayBoard = (p1Type == 2 || p2Type == 2) ? true : false;

    simulateGames(numGames, p1Type, p2Type, displayBoard);

    return 0;
}