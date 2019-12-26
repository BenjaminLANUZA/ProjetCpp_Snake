#ifndef CHEMIN
#define CHEMIN

#include "Element.hh"

class Chemin : public Element{
  public:
    Chemin(int positionX, int positionY):Element(positionX, positionY, true){};
    Chemin(const Chemin& c):Element(c.getX(),c.getY(),true){};
    ~Chemin(){};

    string to_string()const{ return "chemin"; };
    string print()const{ return " "; };

};

#endif /* end of include guard: CHEMIN */
