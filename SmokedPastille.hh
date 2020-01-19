#ifndef SMOKEDPASTILLE
#define SMOKEDPASTILLE
#include <vector>
#include "Pastille.hh"

class SmokedPastille:public Pastille{

public:
  SmokedPastille():Pastille(){
    (this->texture).loadFromFile("images/Pastilles/Smoked_Pastille.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
  }

  SmokedPastille(int positionX, int positionY):Pastille(positionX, positionY){
     (this->texture).loadFromFile("images/Pastilles/Smoked_Pastille.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
    (this->sprite).setPosition(positionX*64.f,positionY*64.f);
  }

  SmokedPastille(const SmokedPastille& s):Pastille(s.getX(),s.getY()){
        (this->texture).loadFromFile("images/Pastilles/Smoked_Pastille.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
    (this->sprite).setPosition(s.getX()*64.f,s.getY()*64.f);
  }

  SmokedPastille(const Chemin& c):Pastille(c){
    (this->texture).loadFromFile("images/Pastilles/Smoked_Pastille.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
  }
  ~SmokedPastille(){}

  string to_string()const{ return "Pastille smoked"; }
  string print()const{ return "s"; }

  void activate(vector<SmokedMur>& mursmoked){
    for(SmokedMur& smoke : mursmoked){
      smoke.activate();
    }
  }

  void disable(vector<SmokedMur>& mursmoked){
    for(SmokedMur& smoke : mursmoked){
      smoke.desactivate();
    }
  }

};

#endif /* end of include guard: SMOKEDPASTILLE */
