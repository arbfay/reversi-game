#include <iostream>
#include <array>
#include <string>
#include <map>
#include "constantes.h"
using namespace std;


class Board{
  array<array<char,SIZE_COL>,SIZE_ROW> board; //Array d'Arrays
  map<char,int> tabL2N;


  public:
    void display(ostream & out = cout) const;
    Board();
    array<array<char,SIZE_COL>,SIZE_ROW> boardCopy() const;
    void convert_Coord(int coord[],string m) ;// prend int et un char et on renvoi un tqbaleau de int
    void move(char color, int nc,int nr);

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
    void wut2flip(vector<int[2]> 2flip, char color,int nc,int nr) const;


};

class Menu{

};
