#ifndef VORTEXMUR
#define VORTEXMUR

#include <algorithm>
#include <cstdlib>
#include "Chemin.hh"
#include "SmokedMur.hh"

using namespace std;

class VortexMur : public SmokedMur{
  public :
  VortexMur(int positionX, int positionY):SmokedMur(positionX, positionY){
      (this->texture).loadFromFile("images/Murs/Mur_Vortex.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(positionX*63.f,positionY*63.f);
  }
  VortexMur(const VortexMur& v):SmokedMur(v.getX(), v.getY()){};
  ~VortexMur(){};

  string to_string()const{ return "mur vortex"; };
  string print()const{ return print_mur_specifique; };
  void activate(){
    this->traversable = true;
    this->print_mur_specifique = "@";
  }
  //on retourne le chemin vers lequel se teleporter
  Chemin& teleportation(vector<Chemin>& c){
    return c[(rand() % ((int)c.size() - 1))];
  }
  void desactivate(){
    this->traversable = false;
    this->print_mur_specifique = "=";
  }
};
#endif /* end of include guard: VORTEXMUR */
