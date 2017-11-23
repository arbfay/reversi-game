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
  //array<char,SIZE_ROW> filler;
  //filler.fill('x');
  //board.fill(filler);
  for(int i=0;i<SIZE_COL;i++){
    for(int j=0;j<SIZE_ROW;j++){
      board[i][j]='.';
    }
  }

  board[3][3]='W'; //Initialisation des pions de départ
  board[3][4]='B';
  board[4][4]='W';
  board[4][3]='B';
  // attribution chiffre a lettre
  tabL2N['a']=0;
  tabL2N['b']=1;
  tabL2N['c']=2;
  tabL2N['d']=3;
  tabL2N['e']=4;
  tabL2N['f']=5;
  tabL2N['g']=6;
  tabL2N['h']=7;
}

/*
* @arg : objet ostream
* @process : ajoute chaque élément de chaque ligne du board à l'objet ostream
*           avec un retour à la ligne à chaque nouvelle ligne du board
* @output : -
*/
void Board::display(ostream & out) const{
  for(int i=0; i<SIZE_COL; i++){
    for ( char x : *(board+i)) { cout << ' ' << x; }
    cout<<'\n';
  }
}

void Board::convert_coord(int coord[],string m){
  coord[0] = get<1>(*tabL2N.find((char) m[0]));
  coord[1] = m[1] - '0' ;
  coord[1]--;
}


void Board::move(char color, int nc, int nr){
  board[nr][nc] = color;
}

tab2d* Board::boardCopy() {
  return board;
}

char Board::getCell(int nc, int nr) const {
  return board[nr][nc];
}
