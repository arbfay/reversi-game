#include "main.h"

using namespace std;

/**
* @arg : -
* @process : ajoute le charactère 'x' à toutes les cellules de l'array board et
*            remplace les charactères centraux par les charactères 'W' et 'B'
*            comme représentation des pions de départ
* @output : -
*/
Board::Board(){
  // Remplir le board par des 'x'
  for(int i=0;i<SIZE_COL;i++){
    for(int j=0;j<SIZE_ROW;j++){
      board[i][j]='.';
    }
  }

  //Initialisation des pions de départ
  board[3][3]='W'; board[3][4]='B';
  board[4][3]='B'; board[4][4]='W';

  //attribution chiffre a lettre
  tabL2N['a']=0; tabL2N['b']=1;
  tabL2N['c']=2; tabL2N['d']=3;
  tabL2N['e']=4; tabL2N['f']=5;
  tabL2N['g']=6; tabL2N['h']=7;
}

/*
* @arg : objet ostream
* @process : ajoute chaque élément de chaque ligne du board à l'objet ostream
*           avec un retour à la ligne à chaque nouvelle ligne du board
* @output : -
*/
void Board::display(ostream & out) const{
  cout<<"  a b c d e f g h"<<endl;
  for(int i=0; i<SIZE_COL; i++){
    cout<<i+1;
    for ( char x : *(board+i)) { cout << ' ' << x; }
    cout<<' ';
    cout<<i+1<<endl;
    cout<<'\n';
  }
  cout<<"  a b c d e f g h"<<endl;
}

/*
* @arg : int coord[] de taille 2 minimum, string m un string avec une lettre
*        suivie d'un chiffre
* @process : insère dans coord[0] le numéro de la colonne entre 0 et 7 correspondant
*            à la lettre, et insière dans coord[1] le numéro de la rangée
*            correspondante sur le board avec le chiffre du string "m"
* @output : -
*/
void Board::convert_coord(int coord[],string m){
  coord[0] = get<1>(*tabL2N.find((char) m[0]));
  coord[1] = m[1] - '0' ;
  coord[1]--;
}

/*
* @arg : color est la lettre à placer sur le board (W ou B), nc est la numéro de
*        la colonne (entre 0 et 7) et nr le numéro de la rangée (entre 0 et 7)
* @process :
* @output : -
*/
void Board::move(char color, int nc, int nr){
  board[nr][nc] = color;
}

tab2d* Board::boardCopy() {
  return board;
}

char Board::getCell(int nc, int nr) const {
  return board[nr][nc];
}

void Board::countPions(int tab[]){
  int counterW = 0;
  int counterB = 0;
  for(int i=0; i<SIZE_COL;i++){
    for(int j = 0; j<SIZE_ROW; j++ ){
      if( board[i][j] == 'W'){
        counterW++;
      }
      else if(board[i][j] == 'B'){
        counterB++;
      }
    }
  }

  tab[0] = counterB;
  tab[1] = counterW;
}
