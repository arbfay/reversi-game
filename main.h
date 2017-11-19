#include <iostream>
#include <array>
#include <string>
#include "constantes.h"
using namespace std;


class Board{
  array<array<char,SIZE_COL>,SIZE_ROW> board; //Array d'Arrays
  public:
    void display(ostream & out = cout) const;
    Board();
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
};

class Menu{

};
