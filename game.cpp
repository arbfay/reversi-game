#include "main.h"
using namespace std;


/*
* @arg : choice est un char qui vaut soit 'H', soit 'A', soit 'F'
*
*/
GameEngine::GameEngine(char choice){
  char c1 = 'W';
  char c2 = 'B';

  //Faire pile ou face pour c1 et c2

  player1 = Player('H', c1);
  player2 = Player(choice, c2);

  //Initialisation du turnOfPlayer à Black
  turnOfPlayer = 'B';

  //Display le board
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
  string name;
  name = (turnOfPlayer=='W') ? player1.getName() : player2.getName();

  cout<< name <<" ("<<turnOfPlayer<<"), entrez votre coup (ex: c4) : "<<endl;
  cin >> result;
  //result = tolower(result);

  return result;
}

void GameEngine::launch(){
  string m="";
  int nombreCoup=4;

  string res;
  cout<<"Comment s'appelle le joueur aux pions noirs (B) ? "<<endl;
  cin >> res;
  player2.setName(res);
  cout<<"Et le joueur aux pions blancs (W) ? "<<endl;
  cin >> res;
  player1.setName(res);

  do{
    /*demander le move du joueur*/
    m = askMove();
    int c[2] ;
    if(m.size() < 3){
      /*executer le move*/
      board.convert_coord(c,m);
      int nc = c[0]; int nr = c[1];
      if(board.getCell(nc,nr) == '.'){
          auto tmp = board.wut2flip(nc,nr);
          cout<<tmp.size()<<endl;
          if(tmp.size() > 0){
            board.flipAll(tmp);
            move(nc,nr); //ajoute le pion du joueur
            updateTurnOfPlayer(); //joueur suivant
            nombreCoup++;
          }
      }

      //system("clear");
      board.display();
      //cout<<nombreCoup<<endl;
    }

    else if(m=="next"){ // Commande pour passer son tour
      updateTurnOfPlayer();
    }
  } while(nombreCoup != 64 && m !="exit");
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

char GameEngine::getTurnOfPlayer(){
  return turnOfPlayer;
}

void GameEngine::setGameEngine(GameEngine* ptr){
  board.setGameEngine(ptr);
}
