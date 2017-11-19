#include <iostream>
#include <map>
#include <string>
#include "main.h"
#include "constantes.h"
using namespace std;




/*
* @arg : choice est un char qui vaut soit 'H', soit 'A', soit 'F'
*
*/
GameEngine::GameEngine(char choice){
  char c1 = 'W';
  char c2 = 'B';
  // Pile ou face pour c1 et c2

  printf("Initialisation des joueurs\n");
  player1 = Player('H', c1);
  player2 = Player(choice, c2);

  //Display le board
  printf("Initialisation du board\n");
  board.display();
}

void GameEngine::updateTurnOfPlayer(){
  if(turnOfPlayer == 'W')
    turnOfPlayer='B';
  else
    turnOfPlayer='W';
}

void GameEngine::move(int nc, int nr){
  //Recupérer la ligne (array)


  if(/*row[nc] != 'x'*/0 ){
    // Move is invalid
  } else {
      board.move(turnOfPlayer,nc,nr);
      updateTurnOfPlayer();

  }
}

string GameEngine::askMove(){
  string result;
  cout<<"Le joueur "<<turnOfPlayer<<", entrez votre coup (ex: c4) : "<<endl;
  cin >> result;
  //result = tolower(result);

  return result;
}

void GameEngine::launch(){
  do{
    /*demander le move du joueur*/
    string m = askMove();
    int c[2] ;
    if(m.size() < 3){
      /*executer le move*/
      board.convert_coord(c,m);

      int nc = c[0];
      int nr = c[1];

      move(nc, nr);
      board.display();
    }
    else {
      /*si 'exit', arrêtez le jeu*/
    }
  }while(1);
}

void GameEngine::wut2flip(vector<int[2]> 2flip, char color, int nc, int nr) const{

  // on veut inscrire les coordonnees des pions a flipper
  // on
  array<array<char,SIZE_COL>,SIZE_ROW> cBoard = board.boardCopy();

  
  for(int i = 0; i<=)
    if(board[nc][nr])
  while ()


}
