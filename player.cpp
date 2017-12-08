#include "main.h"
#include <iostream>
#include <cstdio>
using namespace std;


Player::Player(char typ, char col){
    color = col;
    type = typ;
}

Player::Player(){}


char Player::getType() const{
  return type;
}

char Player::getColor() const{
  return color;
}

void Player::print(ostream & out) const {
  out << "Joueur de type " << type << " et de couleur " << color;
}

void Player::setName(string n){
  name=n;
}

string Player::getName() const {
  return name;
}
