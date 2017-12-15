#include <iostream>
#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <tuple>
#include <map>
#include <chrono>
#include <thread>
#include "constantes.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <future>
//#include <random>

using namespace std;

typedef char tab2d[SIZE_COL];
class GameEngine;
void print(vector<array<int,2>> vec);

void print(vector<array<int,2>> vec);


class Board{
  tab2d board[SIZE_ROW];
  map<char,int> tabL2N;
  GameEngine* game;
  public:
    void display(ostream & out = cout) const;
    Board();
    void initialize(tab2d* init);
    tab2d* boardCopy();
    void setGameEngine(GameEngine* ptr);
    void convert_coord(int coord[],string m) ;// prend int et un char et on renvoi un tqbaleau de int
    string convert_coord_inv(int nc, int nr);
    void move(char color, int nc,int nr);
    char getCell(int nc, int nr) const;
    void countPions(int tab[]);
    vector<array<int,2>> wut2flip(char color, int nc,int nr);
    const vector<tuple<char,int,int>> getPions(int nc, int nr, int direction);
    void flipAll(vector<array<int,2>> coord2flip, int virtuality=0, char color='.');
    vector<array<int,2>> whatLegalMoves(char color);
};


class Player{
  char type; //H for human or F for file or A for artificial intelligence
  char color; //W for white & B for black
  string name; //'Skynet' for AI, ask player's name otherwise
  public:
    char getType() const;
    char getColor() const;
    string getName() const;
    void print(ostream & out = cout) const;
    Player(char typ, char col, char* name);
    Player(char typ, char col);
    Player();
    void setName(string n);
    //virtual string askMove();
};

class GameEngine{
  Player player1;
  Player player2;
  Board board; //Initialise le board
  char turnOfPlayer;
  void updateTurnOfPlayer();
  public:
    GameEngine(char choice);
    void move(int nc, int nr, char color);
    string askMove(); //la déplacer dans Player
    void setGameEngine(GameEngine* ptr);
    void launch();
    void launchWithSkynet();
    void launchWithFile();
    char getTurnOfPlayer();
    string askSkynetMove();
    vector<array<int,2>> filterMoves(vector<array<int,2>> legalMoves);
    float montecarlo(array<int,2> move, char color);
    //vector<array<int,2>> wut2flip(int nc,int nr); //la déplacer dans Board
    //const vector<tuple<char,int,int>> getPions(int nc, int nr, int direction);//la déplacer dans Board
    //void flipAll(vector<array<int,2>> coord2flip);// la déplacer dans Board
};
