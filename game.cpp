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

  //Faire pile ou face pour c1 et c2

  printf("Initialisation des joueurs\n");
  player1 = Player('H', c1);
  player2 = Player(choice, c2);

  //Initialisation du turnOfPlayer à Black
  turnOfPlayer = 'B';

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
  if(/*row[nc] != '.'*/0 ){
    // Move is invalid
  } else {
      board.move(turnOfPlayer,nc,nr);
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
  string m="";
  int nombreCoup=4;
  do{
    /*demander le move du joueur*/
    m = askMove();
    int c[2] ;
    if(m.size() < 3){
      /*executer le move*/

      board.convert_coord(c,m);
      int nc = c[0]; int nr = c[1];
      if(board.getCell(nc,nr) == '.'){
          auto tmp = wut2flip(nc,nr);
          if(tmp.size() > 0){
            flipAll(tmp);
            move(nc,nr); //ajoute le pion du joueur
            updateTurnOfPlayer(); //joueur suivant
          }
      }
      //cout<<nombreCoup<<endl;

      system("clear");
      board.display();
      nombreCoup++;
      cout<<nombreCoup<<endl;
      //for(int i =0; j<SIZE_COL;i++)
    }

    else {
      /*si 'exit', arrêtez le jeu*/
    }
  }while(nombreCoup != 64 && m !="exit" );

  int counter[2];
  board.countPions(counter);

  if(counter[0] < counter[1]){
    cout<<"le joueur W a remporte : "<<counter[1]<<endl;
  }
  else if (counter[0] > counter[1]){
    cout<<"le joueur B a remporte : "<<counter[0]<<endl;
  }
  else{cout<<"Match nul"<<endl;}

}

vector<array<int,2>> GameEngine::wut2flip(int nc, int nr){

  //char directions[8]={"e","ne","n","nw","w","sw","s","se"};
  int directions[8]={1,2,3,4,5,6,7,8};

  vector<array<int,2>> toFlip;
  vector<array<int,2>> tmpToFlip;
  int trigger = 0;

  for(int i=0;i<8;i++){

    vector<tuple<char,int,int>> dirVectors=getPions(nc,nr,directions[i]); //reçoit le vecteur des pions dans toutes les directions

    for(int j=0; j < dirVectors.size() ; j++){
      tuple<char,int,int>tup = dirVectors.at(j);
      trigger = 0;

      char tmpChar = get<0>(tup);
      int tmpCoordC = get<1>(tup);
      int tmpCoordR = get<2>(tup);

      if(tmpChar != turnOfPlayer){ //tant qu'on arrive pas à char égal à celui du joueur, c'est que le pion est à tourner
          array<int,2> tmp ={tmpCoordC, tmpCoordR};
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
      toFlip.insert(toFlip.end(), tmpToFlip.begin(), tmpToFlip.end());
    }
  }//fin de la boucle for sur tous les vecteurs
  return toFlip;
}

const vector<tuple<char,int,int>> GameEngine::getPions(int nc, int nr, int direction){
  //1- Récupérer la ligne nr du board
  tab2d* cBoard = board.boardCopy();

  //2- Itérer sur ]nc, SIZE_ROW] en s'arrêtent à '.' et enregistrer la série de lettre dans un vector
  vector<tuple<char,int,int>> results;

  char elem;
  int coord[2];

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

    if(elem!='.'){
      auto tmp = make_tuple(elem, coord[0], coord[1]);
      //results.insert(results.begin(), tmp);
      results.push_back(tmp);
    } else {
      i=SIZE_ROW+1;
    }
  }

  return results;
}

void GameEngine::flipAll(vector<array<int,2>> coord2flip){
  for(int i = 0; i<coord2flip.size();i++){
    array<int,2> tmp = coord2flip.at(i);
    move(tmp[0],tmp[1]);
  }
}
