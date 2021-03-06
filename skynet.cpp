#include "main.h"
using namespace std;

string GameEngine::askSkynetMove(char color){
  auto legalMoves = board.whatLegalMoves(color);
  if(legalMoves.size() == 0){
    return "next";
  }
  //filtrer les legalMoves
  auto flm = filterMoves(legalMoves);

  //faire montecarlo pour les moves filtrés
  future<float> amc1 = async(std::launch::async,&GameEngine::montecarlo,this, flm.at(0), color); //existe dans tous les cas
  future<float> amc2, amc3;
  if(flm.size()>1)
    amc2 = async(std::launch::async,&GameEngine::montecarlo,this, flm.at(1), color);

  if(flm.size()>2)
    amc3 = async(std::launch::async,&GameEngine::montecarlo,this, flm.at(2), color);

  //cout<<"Starting MC"<<endl;
/*  float mc1 = flm.size() > 0 ? montecarlo(flm.at(0), color) : 0.0;
  //cout<<"MC1 done"<<endl;
  float mc2 = flm.size() > 1 ? montecarlo(flm.at(1), color) : 0.0;
  //cout<<"MC2 done"<<endl;
  float mc3 = flm.size() > 2 ? montecarlo(flm.at(2), color) : 0.0;
  //cout<<"MC3 done"<<endl;
*/
  float mc1 = amc1.get();
  float mc2 = flm.size()>1 ? amc2.get() : 0.0;
  float mc3 = flm.size()>2 ? amc3.get() : 0.0;
  cout<<"Async out"<<endl;

  //choisir la coord avec la plus grande valeur
  array<int,2> choicedCoord;
  if(mc1 >= mc2 && mc1 >= mc3 && flm.size()>0){
    choicedCoord = flm.at(0);
  } else if (mc2 > mc1 && mc2 > mc3 && flm.size()>1){
    choicedCoord = flm.at(1);
  } else if (flm.size()>2){
    choicedCoord = flm.at(2);
  } else {
    return "next";
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

        tmpTurnOfPlayer = tmpTurnOfPlayer=='W' ? 'B' : 'W';
      }
        //this_thread::sleep_for(chrono::milliseconds(100));
    }

    int winnerTab[2];
    virtualBoard.countPions(winnerTab);
    if((color == 'B' && winnerTab[0] > winnerTab[1]) || (color == 'W' && winnerTab[0] < winnerTab[1]))
      countWin++;
  }
  return ((float)countWin/(float)MAX_IT);
}

bool compareCoord (array<int,2> a, array<int,2> b){
  return boardWeights[get<0>(a)][get<1>(a)] >= boardWeights[get<0>(b)][get<1>(b)];
}

vector<array<int,2>> GameEngine::filterMoves(vector<array<int,2>> legalMoves){
    // on va utiliser 'sort' de complexite nlogn avec cette fonction de comparaison
    sort(legalMoves.begin(), legalMoves.end(), compareCoord);

    // nous gardons uniquement les 3 premiers elements de legalMoves triés
    int tmp = legalMoves.size()>=3 ? 3 : legalMoves.size();
    legalMoves.erase(legalMoves.begin()+tmp, legalMoves.end());

    return legalMoves;
}
