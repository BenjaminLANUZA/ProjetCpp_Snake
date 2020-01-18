#ifndef EATABLEVORTEX
#define EATABLEVORTEX

#include "Pastille.hh"
class EatablePastille:public Pastille{
public:
  EatablePastille():Pastille(){};
  EatablePastille(int positionX, int positionY):Pastille(positionX, positionY){
      (this->texture).loadFromFile("images/Pastilles/Eatable_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(positionX*63.f,positionY*63.f);}
  }
  EatablePastille(const EatablePastille& e):Pastille(e.getX(),e.getY()){}
  EatablePastille(const Chemin& c):Pastille(c){}
  ~EatablePastille(){}

  string to_string()const{
    stringstream s;
    s << "Pastille eatable - position x " << x << " ; y " << y << endl;
    return s.str();
  }
  string print()const{ return "e"; }

};

#endif /* end of include guard: EATABLEVORTEX */
