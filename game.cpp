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
  //create the table of weights put at 0

  int N = 1000;
  int M = 100;
  float averagedWW[SIZE_ROW][SIZE_COL]; //final results will be here
  float averagedWB[SIZE_ROW][SIZE_COL];
  float listOfCalculatedWeightsW[M][SIZE_ROW][SIZE_COL]; //list of the weights calculated for each montecarlo
  float listOfCalculatedWeightsB[M][SIZE_ROW][SIZE_COL];

  for(int it = 0; it < M; it++){
    float weightsForWhite[SIZE_ROW][SIZE_COL];
    float weightsForBlack[SIZE_ROW][SIZE_COL];
    for(int i = 0; i<SIZE_ROW; i++){
      for(int j = 0; j<SIZE_COL; j++){
        weightsForWhite[i][j]=0.0;
        weightsForBlack[i][j]=0.0;
      }
    }
    //make the modified montecarlo
    for(int i=0; i<N; i++){
      srand(time(NULL));

      vector<array<int,2>> pathW;
      vector<array<int,2>> pathB;

      tab2d* bc = board.boardCopy();
      Board virtualBoard;
      virtualBoard.initialize(bc);

      char color = 'B';
      auto firstLegalMoves = virtualBoard.whatLegalMoves(color);
      auto move = firstLegalMoves.at(rand() % firstLegalMoves.size()); // choix aléatoire du premier move

      virtualBoard.flipAll(virtualBoard.wut2flip(color,get<0>(move), get<1>(move)),1,color);
      virtualBoard.move(color, get<0>(move), get<1>(move)); // execute le move proposé

      int countPion[2];
      virtualBoard.countPions(countPion);
      int pionsCount = countPion[0] + countPion[1];

      char tmpTurnOfPlayer = color== 'W' ? 'B' : 'W'; // initialise au tour du prochain
      for(int j = 0; j < (SIZE_COL*SIZE_ROW) - pionsCount; j++){
        auto tmpLegalMoves = virtualBoard.whatLegalMoves(tmpTurnOfPlayer);

        int tmpSize = tmpLegalMoves.size();

        if(tmpSize == 0){
          int tmpCountPion[2];
          virtualBoard.countPions(tmpCountPion);
          //virtualBoard.display();
          if(tmpCountPion[0] == 0 || tmpCountPion[1] == 0){
            j = j + (SIZE_COL*SIZE_ROW) - pionsCount + 1;
          } else {
            auto tmpLegalMovesForW = virtualBoard.whatLegalMoves('W');
            auto tmpLegalMovesForB = virtualBoard.whatLegalMoves('B');

            if(tmpLegalMovesForB.size() == 0 && tmpLegalMovesForW.size() == 0){ //Si ni l'un ni l'autre ne sait jouer, arrêter le jeu virtuel
              break;
            } else {
              j--;
              tmpTurnOfPlayer = tmpTurnOfPlayer=='W' ? 'B' : 'W';
            }
          }

        } else {
          int numVec = rand() % tmpSize;
          array<int,2> choicedVec = tmpLegalMoves.at(numVec);

          auto tmpW2f = virtualBoard.wut2flip(tmpTurnOfPlayer,get<0>(choicedVec),get<1>(choicedVec));

          virtualBoard.flipAll(tmpW2f,1,tmpTurnOfPlayer);
          virtualBoard.move(tmpTurnOfPlayer, get<0>(choicedVec), get<1>(choicedVec));

          if(tmpTurnOfPlayer=='W'){ // ajoute au path le move choisi
            pathW.push_back(choicedVec);
          } else {
            pathB.push_back(choicedVec);
          }

          tmpTurnOfPlayer = tmpTurnOfPlayer=='W' ? 'B' : 'W';
        }
          //this_thread::sleep_for(chrono::milliseconds(100));
      }

      int winnerTab[2];
      virtualBoard.countPions(winnerTab);

      if(winnerTab[0] < winnerTab[1]){// white is winner
        for(int i =0; i<pathW.size(); i++){// adding the weights
          array<int,2> coW = pathW.at(i);
          weightsForWhite[get<0>(coW)][get<1>(coW)] += 1;
        }
      } else if(winnerTab[0] > winnerTab[1]){//black is winner
        for(int i =0; i<pathB.size(); i++){//adding the weights
          array<int,2> coB = pathB.at(i);
          weightsForBlack[get<0>(coB)][get<1>(coB)] += 1;
        }
      }
      pathW.clear();// clear for the next game;
      pathB.clear();
    }

    //normalize the weights
    for(int i = 0; i<SIZE_ROW; i++){
      for(int j = 0; j<SIZE_COL; j++){
        weightsForBlack[i][j] /= N;
        weightsForWhite[i][j] /= N;
        listOfCalculatedWeightsB[it][i][j] = weightsForBlack[i][j];
        listOfCalculatedWeightsW[it][i][j] = weightsForWhite[i][j];
      }
    }
  }

  //initialise averagedWB/W
  for(int i = 0; i<SIZE_ROW; i++){
    for(int j = 0; j<SIZE_COL; j++){
      averagedWB[i][j]=0.0;
      averagedWW[i][j]=0.0;
    }
  }
  //sum all the calculated weights per cell
  for(int it = 0; it < M; it++){
    for(int i = 0; i < SIZE_ROW; i++){
      for(int j = 0; j < SIZE_COL; j++){
        averagedWB[i][j] += listOfCalculatedWeightsB[it][i][j];
        averagedWW[i][j] += listOfCalculatedWeightsW[it][i][j];
      }
    }
  }

  //divide the values of the cells by M to get the average
  for(int i = 0; i < SIZE_ROW; i++){
    for(int j = 0; j < SIZE_COL; j++){
      averagedWB[i][j] /= M;
      averagedWW[i][j] /= M;
    }
  }

  //print the weights for black
  cout<<"\n-----Average weights for player B-----"<<endl;
  for(int i = 0; i<SIZE_ROW; i++){
    for(int j = 0; j<SIZE_COL; j++){
      cout<<" | "<<averagedWB[i][j];
    }
    cout<<" | "<<endl;
  }

  cout<<"\n\n-----Average weights for player W-----"<<endl;
  for(int i = 0; i<SIZE_ROW; i++){
    for(int j = 0; j<SIZE_COL; j++){
      cout<<" | "<<averagedWW[i][j];
    }
    cout<<" | "<<endl;
  }

  //repeat & average the normalized weights
}
