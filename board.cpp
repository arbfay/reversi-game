#include "main.h"
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

/**
* @arg : -
* @process : ajoute le charactère 'x' à toutes les cellules de l'array board et
*            remplace les charactères centraux par les charactères 'W' et 'B'
*            comme représentation des pions de départ
* @output : -
*/
Board::Board(){
  for(int i = 0; i<SIZE_COL; i++){ //Complexite = n²
    board[i].fill('x'); // fonction de complexité n
  }
  board[3][3]='W'; //Initialisation des pions de départ
  board[3][4]='B';
  board[4][4]='W';
  board[4][3]='B';
}

/*
* @arg : objet ostream
* @process : ajoute chaque élément de chaque ligne du board à l'objet ostream
*           avec un retour à la ligne à chaque nouvelle ligne du board
* @output : -
*/
void Board::display(ostream & out) const{
  for(int i=0; i<SIZE_COL; i++){
    for ( char x : board[i]) { cout << ' ' << x; }
    cout<<'\n';
  }
}
