#ifndef JEU
#define JEU

#include <thread>
#include "Partie.hh"
#include "Partiesimple.hh"
#include "Partiecomplex.hh"
#include "Complexite.hh"

using namespace std;

class Jeu{
private:
  Partie game;

public:
  Jeu():game(Partiesimple()){//partie simple

  }
  Jeu(Complexite c):game(Partiecomplex(c)){//partie

  }
  ~Jeu(){}
};

#endif /* end of include guard: JEU */
