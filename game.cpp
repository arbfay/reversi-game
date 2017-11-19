#include <iostream>
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
  array<int,SIZE_ROW> row = board[nr];

  if(*cell != 'x'){
    // Move is invalid
  } else {
      row[nc] = turnOfPlayer;
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

    if(m.size() > 2){
      /*interpréter m en nr et nc*/
      int nc = TABL2N.find((char)m[0]);
      int nr =  m[1] - '0';
      /*executer le move*/
      move(nc, nr);
      board.display();
    }
    else {
      /*si 'exit', arrêtez le jeu*/
    }
  }while(/*soit le board est rempli, soit plus de pions W, soit plus de pions B | si exit, break*/)
}
