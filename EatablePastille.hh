#ifndef EATABLEVORTEX
#define EATABLEVORTEX

#include "Pastille.hh"
class EatablePastille:public Pastille{
public:
  EatablePastille():Pastille(){
        cout<<"construct pastille eatable"<<endl; 
      (this->texture).loadFromFile("images/Pastilles/Eatable_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
        (this->sprite).setPosition(500.f,500.f);
        std::cout<<"connar défault"<< std::endl;

  };
  EatablePastille(int positionX, int positionY):Pastille(positionX, positionY){
    cout<<"construct pastille eatable"<<endl; 
      (this->texture).loadFromFile("images/Pastilles/Eatable_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(500.f,500.f);
  }
  EatablePastille(const EatablePastille& e):Pastille(e.getX(),e.getY()){
        cout<<"construct pastille eatable"<<endl; 
      (this->texture).loadFromFile("images/Pastilles/Eatable_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(500.f,500.f);

  }
  EatablePastille(const Chemin& c):Pastille(c){
     (this->texture).loadFromFile("images/Pastilles/Eatable_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
        (this->sprite).setPosition(500.f,500.f);
          std::cout<<"connar chemin"<< std::endl;

  }
  ~EatablePastille(){}

  string to_string()const{
    stringstream s;
    s << "Pastille eatable - position x " << x << " ; y " << y << endl;
    return s.str();
  }
  string print()const{ return "e"; }

};

#endif /* end of include guard: EATABLEVORTEX */
