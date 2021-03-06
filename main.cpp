#include <iostream>
#include <cstdio>
#include "main.h"
using namespace std;

int boardWeights[8][8]={{10,-10,5,5,5,5,-10,10},
  {-10,-10,-5,-5,-5,-5,-10,-10},
  {5,-5,0,0,0,0,-5,5},
  {5,-5,0,0,0,0,-5,5},
  {5,-5,0,0,0,0,-5,5},
  {5,-5,0,0,0,0,-5,5},
  {-10,-10,-5,-5,-5,-5,-10,-10},
  {10,-10,5,5,5,5,-10,10}};
char choice_menu();

int main(){
	char choice = choice_menu();
	GameEngine game(choice);

	game.setGameEngine(&game);

  if(choice == 'H'){
    game.launch();
  } else if (choice == 'A'){
    game.launchWithSkynet();
  } else if (choice == 'F'){
    cout<<"Utiliez le fichier './file_player.txt' pour jouer"<<endl;
    string path("./file_player.txt");
    game.launchWithFile(path);
  } else if (choice == 'G'){
    game.generateWeights();
  }

	return 0;
}

char choice_menu(){
	cout << "Bonjour et bienvenue dans le jeu de reversi de la mort qui tue.\n"<<endl;
	char choice;
	do {
		cout << "Choisissez un mode de jeu :\n"<< "H - Jouer contre un Hooman\n" << "A - Jouer contre Skynet\n" << "F - Jouer contre un script\n" <<endl;
		cin >> choice;
		choice=toupper(choice);
	} while(choice != 'H' && choice != 'A' && choice != 'F' && choice != 'G');
	return choice;
}

void print(vector<array<int,2>> vec){
  cout<<"Impression de vector : "<<endl;
  for(int i=0; i<vec.size();i++){
    array<int,2> arr = vec.at(i);
    cout<<"Element "<<i<<" : ("<< get<0>(arr) <<", "<<get<1>(arr) <<") "<<endl;
  }
}
