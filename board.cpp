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

/*Board::Board(GameEngine* ptrGame){
  Board();
  game = ptrGame;
}*/

Board::Board(tab2d* init){
  for(int i=0; i<SIZE_COL;i++){
    for(int j=0; i<SIZE_ROW; j++){
      board[i][j] = init[i][j];
    }
  }
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
    cout<<i+1;
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

// les coord en sortie sont dans l'ordre "COL, ROW"
// mais le board est organisé en "ROW, COL"
vector<array<int,2>> Board::wut2flip(char color, int nc, int nr){

  //char directions[8]={"e","ne","n","nw","w","sw","s","se"};
  int directions[8]={1,2,3,4,5,6,7,8};

  vector<array<int,2>> toFlip;
  vector<array<int,2>> tmpToFlip;
  int trigger = 0;
  char turnOfPlayer = color;
  if(board[nr][nc] == '.'){
    for(int i=0; i<8; i++){
      vector<tuple<char,int,int>> dirVectors=getPions(nc,nr,directions[i]); //reçoit le vecteur des pions dans toutes les directions

      for(int j=0; j < dirVectors.size() ; j++){
        tuple<char,int,int>tup = dirVectors.at(j);
        trigger = 0;

        char tmpChar = get<0>(tup);
        int tmpCoordC = get<1>(tup);
        int tmpCoordR = get<2>(tup);
        //cout<<"tuple : ("<<tmpChar<<", "<< tmpCoordC << ", "<< tmpCoordR <<")"<<endl;

        if(tmpChar != turnOfPlayer ){ //tant qu'on arrive pas à char égal à celui du joueur, c'est que le pion est à tourner
            array<int,2> tmp = {tmpCoordC, tmpCoordR};
            tmpToFlip.push_back(tmp);
        }
        if(tmpChar == turnOfPlayer) {
          trigger = 1;
          j = dirVectors.size()+1;
        }
      }// fin de la boucle for sur un des vecteurs directionnels

      if(trigger==0){
        tmpToFlip.clear();
      } else {
        //insert tmpToFlip in toFlip
        //cout<<"wut2flip (tmp) size : "<< tmpToFlip.size()<<endl;
        toFlip.insert(toFlip.end(), tmpToFlip.begin(), tmpToFlip.end());
        tmpToFlip.clear();
      }
    }
  }//fin de la boucle for sur tous les vecteurs
    //cout<<"wut2flip size : "<< toFlip.size()<<endl;
    return toFlip;
}

const vector<tuple<char,int,int>> Board::getPions(int nc, int nr, int direction){
  //1- Récupérer la ligne nr du board
  tab2d* cBoard = boardCopy();

  //2- Itérer sur ]nc, SIZE_ROW] en s'arrêtent à '.' et enregistrer la série de lettre dans un vector
  vector<tuple<char,int,int>> results;

  char elem;
  int coord[2];
  //cout<<"Direction : "<<direction<<endl;
  for(int i = 1; i<SIZE_ROW;i++){
    switch(direction){
      case 1:
        elem=cBoard[nr][nc+i];
        coord[0]=nc+i;
        coord[1]=nr;
        break;
      case 2:
        elem=cBoard[nr-i][nc+i];
        coord[0]=nc+i;
        coord[1]=nr-i;
        break;
      case 3:
        elem=cBoard[nr-i][nc];
        coord[0]=nc;
        coord[1]=nr-i;
        break;
      case 4:
        elem=cBoard[nr-i][nc-i];
        coord[0]=nc-i;
        coord[1]=nr-i;
        break;
      case 5:
        elem=cBoard[nr][nc-i];
        coord[0]=nc-i;
        coord[1]=nr;
        break;
      case 6:
        elem=cBoard[nr+i][nc-i];
        coord[0]=nc-i;
        coord[1]=nr+i;
        break;
      case 7:
        elem=cBoard[nr+i][nc];
        coord[0]=nc;
        coord[1]=nr+i;
        break;
      case 8:
        elem=cBoard[nr+i][nc+i];
        coord[0]=nc+i;
        coord[1]=nr+i;
        break;
    }

    if(elem != '.' && (elem == 'W' || elem == 'B') && (coord[0]>=0 && coord[1]>=0) && (coord[0]<SIZE_COL && coord[1]<SIZE_ROW)){
      //cout<<elem<<" ("<<coord[0]<<", "<<coord[1]<<")"<<endl;
      auto tmp = make_tuple(elem, coord[0], coord[1]);
      //results.insert(results.begin(), tmp);
      results.push_back(tmp);
    } else {
      i=SIZE_ROW+1;
    }
  }

  return results;
}

void Board::flipAll(vector<array<int,2>> coord2flip, int virtuality, char color){ //
  if(virtuality){
    for(int i = 0; i<coord2flip.size();i++){
      array<int,2> tmp = coord2flip.at(i);
      move(color,tmp[0],tmp[1]);
    }
  } else{
    for(int i = 0; i<coord2flip.size();i++){
      array<int,2> tmp = coord2flip.at(i);
      game->move(tmp[0],tmp[1]);
    }
  }
}

void Board::setGameEngine(GameEngine* ptr){
  game = ptr;
}

vector<array<int,2>> Board::whatLegalMoves(char color){//quels sont les moves legaux pour cette couleur

  set<array<int,2>> results;

  //Liste des cases vides autour des pions de couleur !color
  for(int i=0;i<SIZE_COL;i++){
    for(int j=0; j<SIZE_ROW; j++){
      char c = board[j][i];

      //Calculer les gains potentiels pour chacune de ces cases
      //Si gain dans au moins une direction, on garde la case
      if(c != color && c != '.'){
          cout<< "Char c : "<< c << ", color : "<< color <<endl;
          vector<array<int,2>> east = wut2flip(color,i+1,j); // verifier que [i+1,j] est '.'
          vector<array<int,2>> neast = wut2flip(color,i+1,j-1);
          vector<array<int,2>> north = wut2flip(color,i,j-1);
          vector<array<int,2>> nwest = wut2flip(color,i-1,j-1);
          vector<array<int,2>> west = wut2flip(color,i-1,j);
          vector<array<int,2>> swest = wut2flip(color,i-1,j+1);
          vector<array<int,2>> south = wut2flip(color,i,j+1);
          vector<array<int,2>> seast = wut2flip(color,i+1,j+1);

          if(east.size() > 0){
            array<int,2> coord = {i+1,j};
            results.emplace(coord);
            east.clear();
          }
          if(neast.size() > 0){
            array<int,2> coord = {i+1,j-1};
            results.emplace(coord);
            neast.clear();
          }
          if(north.size() > 0){
            array<int,2> coord = {i,j-1};
            results.emplace(coord);
            north.clear();
          }
          if(nwest.size() > 0){
            array<int,2> coord = {i-1,j-1};
            results.emplace(coord);
            nwest.clear();
          }
          if(west.size() > 0){
            array<int,2> coord = {i-1,j};
            results.emplace(coord);
            west.clear();
          }
          if(swest.size() > 0){
            array<int,2> coord = {i-1,j+1};
            results.emplace(coord);
            swest.clear();
          }
          if(south.size() > 0){
            array<int,2> coord = {i,j+1};
            results.emplace(coord);
            south.clear();
          }
          if(seast.size() > 0){
            array<int,2> coord = {i+1,j+1};
            results.emplace(coord);
            seast.clear();
          }
      }
    }
  }
  //Retourner les cases avec gain
  //print(results);
  vector<array<int,2>> toReturn(results.begin(), results.end());
  return toReturn;
};
