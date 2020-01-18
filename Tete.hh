#ifndef TETE
#define TETE
#include "Body.hh"

class Tete : public Body{

public:
  Tete():Body(){}
  Tete(int positionX, int positionY):Body(positionX, positionY){
     (this->texture).loadFromFile("images/Snake/Tete_Snake_Droite.png", sf::IntRect(0, 0, 63, 63))
    this->sprite.setTexture(this->texture);
    (this->sprite).setPosition(positionX*63.f,positionY*63.f);
  }
  Tete(const Tete& t):Body(t.getX(),t.getY()){}
  Tete(const Body& b):Body(b.getX(),b.getY()){}
  ~Tete(){}

  string to_string()const{
    stringstream s;
    s << "Tete" << endl;
    return s.str();
  }
  string print()const{ return "0"; }
  //fonction indiquant a la tete l'action a effectuer lorsqu elle rencontre un autre element
  bool action(const Element& e)const{return false;}

};


#endif /* end of include guard: TETE */
