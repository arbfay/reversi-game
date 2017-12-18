#include "main.h"
using namespace std;


/*
* @arg : choice est un char qui vaut soit 'H', soit 'A', soit 'F'
*
*/
GameEngine::GameEngine(char choice){
  char c1 = 'B';
  char c2 = 'W';

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

void GameEngine::move(int nc, int nr, char color){
  board.move(color,nc,nr);
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
  system("clear");
  board.display();
  string m="";
  int nombreCoup=4;

  string res;
  cout<<"Comment s'appelle le joueur aux pions noirs (B) ? "<<endl;
  cin >> res;
  player2.setName(res);
  cout<<"\nEt le joueur aux pions blancs (W) ? "<<endl;
  cin >> res;
  player1.setName(res);

  system("clear");
  board.display();

  do{
    m = askMove();
    int c[2] ;
    if(m.size() < 3){
      /*executer le move*/
      board.convert_coord(c,m);
      int nc = c[0]; int nr = c[1];
      char cell = board.getCell(nc,nr);
      if( cell != 'W' && cell != 'B'){
          auto tmp = board.wut2flip(turnOfPlayer,nc,nr);

          if(tmp.size() > 0){
            board.flipAll(tmp,0,turnOfPlayer);
            move(nc,nr,turnOfPlayer); //ajoute le pion du joueur
            updateTurnOfPlayer(); //joueur suivant
            nombreCoup++;
          }
      }
      system("clear");
      board.display();
    }

    else if(m=="next"){ // Commande pour passer son tour
      updateTurnOfPlayer();
    }
  } while(nombreCoup != 64 && m !="exit");
  int counter[2];
  board.countPions(counter);

  if(counter[0] < counter[1]){
    cout<<"le joueur W a remporté la partie avec "<<counter[1]<<" pions."<<endl;
  }
  else if (counter[0] > counter[1]){
    cout<<"le joueur B a remporté la partie avec "<<counter[0]<<" pions."<<endl;
  }
  else{cout<<"Match nul !"<<endl;}
}

void GameEngine::launchWithSkynet(){
  system("clear");
  board.display();
  string m="";
  int nombreCoup=4;
  int c[2] ;

  do{
    int trigH = 0;
    do{
      m = askSkynetMove(player1.getColor());
      if(m.size() < 3){
        /*executer le move*/
        board.convert_coord(c,m);
        int nc = c[0]; int nr = c[1];
        char cell = board.getCell(nc,nr);
        if( cell != 'W' && cell != 'B'){
            auto tmp = board.wut2flip(player1.getColor(),nc,nr);
            if(tmp.size() > 0){
              board.flipAll(tmp,0, player1.getColor());
              board.move(player1.getColor(),nc,nr); //ajoute le pion du joueur
              //updateTurnOfPlayer(); //joueur suivant
              nombreCoup++;
              trigH = 1;
            }
        }
      } else if (m == "next"){
        trigH=1;
      }
    }while(!trigH);

    board.display();
    cout<<"Skynet choisit son prochain mouvement..."<<endl;
    string m2 = askSkynetMove(player2.getColor());
    //system("clear");
    //board.display();

    cout<<"Skynet a choisi : "<<m2<<endl;
    if(m.size() < 3){ //si askMove renvoit 'next' ou autre -> ne joue pas
      board.convert_coord(c, m2);
      int nc = c[0]; int nr = c[1];
      char cell = board.getCell(nc,nr);
      if( cell != 'W' && cell != 'B'){
          auto tmp = board.wut2flip(player2.getColor(),nc,nr);
          if(tmp.size() > 0){
            board.flipAll(tmp,0,player2.getColor());
            board.move(player2.getColor(),nc,nr); //ajoute le pion du joueur
            nombreCoup++;
          }
      }
    } else {
      auto tmpLegalMovesForW = board.whatLegalMoves('W');
      auto tmpLegalMovesForB = board.whatLegalMoves('B');
      if(tmpLegalMovesForB.size() == 0 && tmpLegalMovesForW.size() == 0){
        nombreCoup=64;
      }
    }

    //system("clear");
    board.display();
  } while(nombreCoup != 64 && m !="exit");

  int counter[2];
  board.countPions(counter);

  if(counter[0] < counter[1]){
    cout<<"Skynet a remporté la partie avec "<<counter[1]<<" pions."<<endl;
  }
  else if (counter[0] > counter[1]){
    cout<<"Le joueur B a remporté la partie avec "<<counter[0]<<" pions."<<endl;
  }
  else{cout<<"Match nul !"<<endl;}
}

char GameEngine::getTurnOfPlayer(){
  return turnOfPlayer;
}

void GameEngine::setGameEngine(GameEngine* ptr){
  board.setGameEngine(ptr);
}

void GameEngine::launchWithFile(){

};


void GameEngine::generateWeights(){
  
}
