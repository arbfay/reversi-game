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

  //test de Skynet
  //askSkynetMove();
  //fn de test

  do{
    /*demander le move du joueur*/
    auto lm=board.whatLegalMoves(turnOfPlayer);
    //cout<<"Legal moves"<<endl;
    //print(lm);

    //cout<<"Filtered legal moves"<<endl;
    auto flm=filterMoves(lm);
    //print(flm);
    float mc = montecarlo(flm.at(0), 'B');
    //cout << mc << endl;
    //this_thread::sleep_for(chrono::milliseconds(1000));
    if(mc){
      cout<<"MC : "<<mc <<endl;
    }

    m = askMove();
    int c[2] ;
    if(m.size() < 3){
      /*executer le move*/
      board.convert_coord(c,m);
      int nc = c[0]; int nr = c[1];
      char cell = board.getCell(nc,nr);
      if( cell != 'W' && cell != 'B'){
          auto tmp = board.wut2flip(turnOfPlayer,nc,nr);
          //print(tmp);
          //cout<<tmp.size()<<endl;
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

bool compareCoord (array<int,2> a, array<int,2> b){
  return boardWeights[get<0>(a)][get<1>(a)] >= boardWeights[get<0>(b)][get<1>(b)];
}

vector<array<int,2>> GameEngine::filterMoves(vector<array<int,2>> legalMoves){
    // on va utiliser 'sort' de complexite nlogn avec cette fonction de comparaison
    sort(legalMoves.begin(), legalMoves.end(), compareCoord);

    // nous gardons uniquement les 3 premiers elements de legalMoves triés
    legalMoves.erase(legalMoves.begin()+3, legalMoves.end());

    return legalMoves;
}

// color = couleur de Skynet
float GameEngine::montecarlo(array<int,2> move, char color){
  // creer un board initiliasé avec le board actuel + le move
  int countWin=0;
  //default_random_engine generator;
  srand(time(NULL));

  // jouer successivement des pions W et B sur le board virtuel


  for(int i=0; i<MAX_IT; i++){
    //cout<< pionsCount <<endl;
    Board virtualBoard;
    //virtualBoard.display();
    virtualBoard.flipAll(virtualBoard.wut2flip(color,get<0>(move), get<1>(move)),1,color);
    virtualBoard.move(color, get<0>(move), get<1>(move)); // execute le move proposé

    int countPion[2];
    virtualBoard.countPions(countPion);
    int pionsCount = countPion[0] + countPion[1];

    char tmpTurnOfPlayer = color== 'W' ? 'B' : 'W'; // initialise au tour du prochain
    for(int j = 0; j < (SIZE_COL*SIZE_ROW) - pionsCount; j++){
      //cout<<j<<endl;
      //virtualBoard.display();
      auto tmpLegalMoves = virtualBoard.whatLegalMoves(tmpTurnOfPlayer);
      //print(tmpLegalMoves);
      // choisir un point random
      //uniform_int_distribution<int> distribution(0,tmpLegalMoves.size());
      int tmpSize = tmpLegalMoves.size();
      //cout<<tmpSize<<endl;
      if(tmpSize == 0){
        int tmpCountPion[2];
        virtualBoard.countPions(tmpCountPion);
        if(tmpCountPion[0] == 0 || tmpCountPion[1] == 0){
          j = j + (SIZE_COL*SIZE_ROW) - pionsCount + 1;
        } else {
          j--;
          tmpTurnOfPlayer = tmpTurnOfPlayer=='W' ? 'B' : 'W';
        }
      } else {
        //cout<<numVec<<endl;
        int numVec = rand() % tmpSize;
        array<int,2> choicedVec = tmpLegalMoves.at(numVec);

        auto tmpW2f = virtualBoard.wut2flip(tmpTurnOfPlayer,get<0>(choicedVec),get<1>(choicedVec));
        //print(tmpW2f);
        virtualBoard.flipAll(tmpW2f,1,tmpTurnOfPlayer);
        virtualBoard.move(tmpTurnOfPlayer, get<0>(choicedVec), get<1>(choicedVec));

        tmpTurnOfPlayer = tmpTurnOfPlayer=='W' ? 'B' : 'W';
      }
        //this_thread::sleep_for(chrono::milliseconds(100));
    }

    int winnerTab[2];
    virtualBoard.countPions(winnerTab);
    if(color == 'B' && winnerTab[0] < winnerTab[1]){
      countWin++;
    }
  }
  cout << "Countwin : "<< countWin<<endl;
  return (float)(countWin/MAX_IT);
}
