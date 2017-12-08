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
#include <time.h>

using namespace std;

typedef char tab2d[SIZE_COL];
class GameEngine;

void print(vector<array<int,2>> vec);


class Board{
  tab2d board[SIZE_ROW];
  map<char,int> tabL2N;
  GameEngine* game;
  public:
    void display(ostream & out = cout) const;
    Board();
    //Board(GameEngine * ptrGame);
    tab2d* boardCopy();
    void setGameEngine(GameEngine* ptr);
    void convert_coord(int coord[],string m) ;// prend int et un char et on renvoi un tqbaleau de int
    void move(char color, int nc,int nr);
    char getCell(int nc, int nr) const;
    void countPions(int tab[]);
    vector<array<int,2>> wut2flip(int nc,int nr);
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
    void move(int nc, int nr);
    string askMove(); //la déplacer dans Player
    void setGameEngine(GameEngine* ptr);
    void launch();
    char getTurnOfPlayer();
    vector<array<int,2>> wut2flip(int nc,int nr); //la déplacer dans Board
    const vector<tuple<char,int,int>> getPions(int nc, int nr, int direction);//la déplacer dans Board
    void flipAll(vector<array<int,2>> coord2flip);// la déplacer dans Board
    //Skynet(char col);
    //string askSkynetMove(char color); //re-implementer askMove pour l'IA devra gerer la couleur independemment du game engine
    //vector<array<int,2>> filterMoves(); selectionne les moves sur lesquels
    //void monteCarlo(); //calcule la probabilité d'avoir un succès selon un move

};
