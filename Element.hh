#ifndef ELEMENT
#define ELEMENT
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
//un element a une position (x,y)
//un element peut etre un Body, une pastille, un mur ou un chemin

class Element{

  protected :
  int x;
  int y;
  bool traversable; //capacite d un element a etre traverse par un autre element
  sf::Texture texture ; 
  sf::Sprite sprite; 

  public :
  Element(){};
  Element(int positionX, int positionY, bool trav):x(positionX),y(positionY),traversable(trav){};
  Element(const Element& e):x(e.getX()),y(e.getY()),traversable(e.is_traversable()){};
  virtual ~Element(){};
  int getX()const{ return x;};
  int getY()const{ return y;};
  sf::Texture getTexture(){return texture;}
  sf::Sprite getSprite(){return sprite;}

  void setPosition(int positionX, int positionY){ 
    this->x = positionX ;
    this->y = positionY;
    //MAJ POSITION SPRITE
    (this->sprite).setPosition(positionX*63.f,positionY*63.f);
  }


  void setPosition(Element& e){
    this->x = e.getX(); 
    this->y = e.getY();
     //MAJ POSITION SPRITE
    (this->sprite).setPosition((this->x)*63.f,(this->y)*63.f);
  }


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
