#ifndef PARTIESIMPLE
#define PARTIESIMPLE

#include "Partie.hh"

class Partiesimple : public Partie{ //private car on veut etre sur que tous les elements heredite de Partie soient private ici
private:

public:
  Partiesimple();
  ~Partiesimple();

  string to_string()const;
  string print()const;
  void action(int positionX, int positionY);
  Element* is_bord_traversable(int positionX, int positionY);
};

#endif /* end of include guard: PARTIESIMPLE */
