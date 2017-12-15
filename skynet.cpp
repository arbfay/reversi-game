#include "main.h"
using namespace std;

string GameEngine::askSkynetMove(){
  auto legalMoves = board.whatLegalMoves(player2.getColor());
  if(legalMoves.size() == 0){
    return "next";
  }
  //filtrer les legalMoves
  auto flm = filterMoves(legalMoves);

  //faire montecarlo pour les moves filtrés
  future<float> amc1 = async(montecarlo, flm.at(0), player2.getColor());
  future<float> amc2 = async(montecarlo, flm.at(1), player2.getColor());
  future<float> amc3 = async(montecarlo, flm.at(2), player2.getColor());
  //print(flm);

  /*cout<<"Starting MC"<<endl;
  float mc1 = montecarlo(flm.at(0), player2.getColor());
  cout<<"MC1 done"<<endl;
  float mc2 = montecarlo(flm.at(1), player2.getColor());
  cout<<"MC2 done"<<endl;
  float mc3 = montecarlo(flm.at(2), player2.getColor());
  cout<<"MC3 done"<<endl;*/
  float mc1 = amc1.get();
  float mc2 = amc2.get();
  float mc3 = amc3.get();

  //choisir la coord avec la plus grande valeur
  array<int,2> choicedCoord;
  if(mc1 >= mc2 && mc1 >= mc3){
    choicedCoord = flm.at(0);
  } else if (mc2 > mc1 && mc2 > mc3){
    choicedCoord = flm.at(1);
  } else {
    choicedCoord = flm.at(2);
  }

  //convertir cette coord en lettre-chiffre

  return board.convert_coord_inv(get<0>(choicedCoord), get<1>(choicedCoord));

}

float GameEngine::montecarlo(array<int,2> move, char color){
  // creer un board initiliasé avec le board actuel + le move
  int countWin=0;

  for(int i=0; i<MAX_IT; i++){
    srand(time(NULL));

    tab2d* bc = board.boardCopy();
    Board virtualBoard;
    virtualBoard.initialize(bc);
    virtualBoard.flipAll(virtualBoard.wut2flip(color,get<0>(move), get<1>(move)),1,color);
    virtualBoard.move(color, get<0>(move), get<1>(move)); // execute le move proposé

    int countPion[2];
    virtualBoard.countPions(countPion);
    int pionsCount = countPion[0] + countPion[1];

    char tmpTurnOfPlayer = color== 'W' ? 'B' : 'W'; // initialise au tour du prochain
    for(int j = 0; j < (SIZE_COL*SIZE_ROW) - pionsCount; j++){
      auto tmpLegalMoves = virtualBoard.whatLegalMoves(tmpTurnOfPlayer);

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
        int numVec = rand() % tmpSize;
        array<int,2> choicedVec = tmpLegalMoves.at(numVec);

        auto tmpW2f = virtualBoard.wut2flip(tmpTurnOfPlayer,get<0>(choicedVec),get<1>(choicedVec));

        virtualBoard.flipAll(tmpW2f,1,tmpTurnOfPlayer);
        virtualBoard.move(tmpTurnOfPlayer, get<0>(choicedVec), get<1>(choicedVec));

        tmpTurnOfPlayer = tmpTurnOfPlayer=='W' ? 'B' : 'W';
      }
        //this_thread::sleep_for(chrono::milliseconds(100));
    }

    int winnerTab[2];
    virtualBoard.countPions(winnerTab);
    if((color == 'B' && winnerTab[0] > winnerTab[1]) || (color == 'W' && winnerTab[0] < winnerTab[1]))
      countWin++;
  }
  return (float)(countWin/MAX_IT);
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
