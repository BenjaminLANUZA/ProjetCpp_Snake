#ifndef BODY
#define BODY

#include "Element.hh"

class Body:public Element{
  public :
  Body():Element(){}
  Body(int positionX, int positionY):Element(positionX,positionY,false){}
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
