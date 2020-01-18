#ifndef BODY
#define BODY

#include "Element.hh"

class Body:public Element{
  public :
  Body():Element(){}
  Body(int positionX, int positionY):Element(positionX,positionY,false){
      (this->texture).loadFromFile("images/Snake/Corps.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(positionX*63.f,positionY*63.f);
  }
  
  Body(const Body& body):Element(body.getX(), body.getY(),false){}
  Body(Element* e):Element(e->getX(), e->getY(), false){}
  ~Body(){}

  string to_string()const{
    stringstream s;
    s << "Body"<< endl;
    return s.str();
  }
  string print()const{ return "o"; }
};

#endif /* end of include guard: BODY */
