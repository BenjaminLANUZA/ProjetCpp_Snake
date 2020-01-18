#ifndef PASTILLE
#define PASTILLE

#include "Element.hh"

using namespace std;

class Pastille:public Element{

public:
  Pastille():Element(){};
  Pastille(int positionX, int positionY):Element(positionX,positionY, true){]
  Pastille(const Pastille& p):Element(p.getX(), p.getY(), true){}
  Pastille(const Chemin& c):Element(c.getX(), c.getY(), true){}
  ~Pastille(){};

  virtual string to_string()const = 0;

};

#endif /* end of include guard: PASTILLE */
