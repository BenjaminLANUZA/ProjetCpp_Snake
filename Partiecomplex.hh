#ifndef PASTILLECOMPLEX
#define PASTILLECOMPLEX

#include "Partie.hh"
#include "Utilities.hh"

class Partiecomplex : public Partie{ //private car on veut etre sur que tous les elements heredite de Partie soient private ici
private :
  vector<Mur> mur;
  vector<SmokedMur> murSmoked;
  vector<VortexMur> murVortex;
  VortexPastille pastilleVortex;
  Complexite complexite; //definit la complexite du jeu (nombre de murs, nombre de pastilles)

public:
  Partiecomplex(Complexite difficulte);
  ~Partiecomplex();
  void action(int positionX, int positionY);
  Element* is_movement_possible(int positionX, int positionY);
  string to_string()const;
  string print()const;

///////EQUIVALENCES/COMPLEXITE/////////////
int equivalence_mur();
int equivalence_mur_specifique();
int equivalence_temporelle();
///////////////////////////////////////////
};

#endif /* end of include guard: PASTILLECOMPLEX */
