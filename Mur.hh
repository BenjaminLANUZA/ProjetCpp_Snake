#ifndef MUR
#define MUR

#include "Element.hh"
class Mur : public Element{

  public :
  Mur():Element(){};
  Mur(int positionX, int positionY):Element(positionX, positionY, false){};
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
