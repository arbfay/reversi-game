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
	game.launch();

	return 0;
}

char choice_menu(){
	cout << "Bonjour et bienvenue dans le jeu de reversi de la mort qui tue.\n"<<endl;
	char choice;
	do {
		cout << "Choisissez un mode de jeu :\n"<< "H - Jouer contre un Hooman\n" << "A - Jouer contre Skynet\n" << "F - Jouer contre un script\n" <<endl;
		cin >> choice;
		choice=toupper(choice);
	} while(choice != 'H' && choice != 'A' && choice != 'F');
	return choice;
}
