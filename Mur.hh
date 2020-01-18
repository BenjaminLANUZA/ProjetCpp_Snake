#ifndef MUR
#define MUR

#include "Element.hh"
class Mur : public Element{

  public :
  Mur():Element(){};
  Mur(int positionX, int positionY):Element(positionX, positionY, false){
    (this->texture).loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0, 0, 63, 63));
    this->sprite.setTexture(this->texture);
    (this->sprite).setPosition(sf::Vector2f(positionX*63.f, positionY*63.f));
  };
  Mur(const Mur& m):Element(m.getX(), m.getY(), false){};
  ~Mur(){};

  string to_string()const{ return "mur"; };
  string print()const{ return "="; };
  const Mur& operator=(const Mur & m){
    const Mur& cp(m);
    return cp;
  }
};

#endif /* end of include guard: MUR */
