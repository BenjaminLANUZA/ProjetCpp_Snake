#ifndef ELEMENT
#define ELEMENT
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
//un element a une position (x,y)
//un element peut etre un Body, une pastille, un mur ou un chemin

class Element{

  protected :
  int x;
  int y;
  bool traversable; //capacite d un element a etre traverse par un autre element

  public :
  Element(){};
  Element(int positionX, int positionY, bool trav):x(positionX),y(positionY),traversable(trav){};
  Element(const Element& e):x(e.getX()),y(e.getY()),traversable(e.is_traversable()){};
  virtual ~Element(){};
  int getX()const{ return x;};
  int getY()const{ return y;};
  void setPosition(int positionX, int positionY){ this->x = positionX ; this->y = positionY;}
  void setPosition(Element& e){this->x = e.getX(); this->y = e.getY();}
  bool is_traversable()const{ return traversable;};
  virtual string to_string()const = 0;
  virtual string print()const = 0;
  friend ofstream& operator<<(ofstream& f, Element& e);

};

inline ofstream& operator<<(ofstream& f, Element& e){
  f << e.x << " " << e.y << endl;
  return f;
}
#endif /* end of include guard: ELEMENT */
