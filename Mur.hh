#ifndef MUR
#define MUR

#include "Element.hh"
class Mur : public Element{

  public :
  Mur():Element(){
     (this->texture).loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
  };
  Mur(int positionX, int positionY):Element(positionX, positionY, false){
    cout<<"construct mur"<<endl; 
    (this->texture).loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
    (this->sprite).setPosition(sf::Vector2f(positionX*64.f, positionY*64.f));
  };
  Mur(const Mur& m):Element(m.getX(), m.getY(), false){
     (this->texture).loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
    (this->sprite).setPosition(sf::Vector2f(m.getX()*64.f, m.getY()*64.f));
  };
  ~Mur(){};

  string to_string()const{ return "mur"; };
  string print()const{ return "="; };
  const Mur& operator=(const Mur & m){
    const Mur& cp(m);
    return cp;
  }
};

#endif /* end of include guard: MUR */
