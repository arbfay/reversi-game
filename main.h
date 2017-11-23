#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <map>
#include <chrono>
#include <thread>
#include "constantes.h"
using namespace std;

typedef char tab2d[SIZE_COL];

class Board{
  //array<array<char,SIZE_COL>,SIZE_ROW> board; //Array d'Arrays
  tab2d board[SIZE_ROW];
  map<char,int> tabL2N;
  public:
    void display(ostream & out = cout) const;
    Board();
    //array<array<char,SIZE_COL>,SIZE_ROW> boardCopy() const;
    tab2d* boardCopy() ;
    void convert_coord(int coord[],string m) ;// prend int et un char et on renvoi un tqbaleau de int
    void move(char color, int nc,int nr);
    char getCell(int nc, int nr) const;
};


class Player{
  char type; //H for human or F for file or A for artificial intelligence
  char color; //W for white & B for black
  public:
    char getType() const;
    char getColor() const;
    void print(ostream & out = cout) const;
    Player(char typ, char col);
    Player();
};

class GameEngine{
  Player player1;
  Player player2;
  Board board; //Initialise le board
  bool hasStarted;
  char turnOfPlayer;
  void updateTurnOfPlayer();
  public:
    GameEngine(char choice);
    void move(int nc, int nr);
    string askMove();
    void launch();
    vector<array<int,2>> wut2flip(int nc,int nr);
    const vector<tuple<char,int,int>> getPions(int nc, int nr, int direction);
    void flipAll(vector<array<int,2>> coord2flip);
};

class Menu{

};
