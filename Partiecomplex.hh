#ifndef PASTILLECOMPLEX
#define PASTILLECOMPLEX

#include "Partie.hh"
#include "Utilities.hh"

class Partiecomplex : public Partie{ //private car on veut etre sur que tous les elements heredite de Partie soient private ici
private :
  vector<Mur> mur;
  vector<SmokedMur> murSmoked;
  vector<VortexMur> murVortex;
  Complexite complexite; //definit la complexite du jeu (nombre de murs, nombre de pastilles)
  bool pastilleVortex_ready;
  //ces attributs stockent l'etat de la position precedente du snake
  int positionX_tete_prec;
  int positionY_tete_prec;

public:
  Partiecomplex(Complexite difficulte);
  Partiecomplex(vector<Chemin>& c, vector<Body>& b, vector<Mur>& m, vector<SmokedMur>& sm, vector<VortexMur>& vm, EatablePastille& e, SmokedPastille& s, VortexPastille& v, int& score):Partie(c, b, e, s, v, score),mur(m),murSmoked(sm),murVortex(vm){
    placeElement(murVortex);
    placeElement(murSmoked);
    placeElement(mur);
  }
  ~Partiecomplex();
  //operateur permettant de formatter la sauvegarde de la partie sur un fichier
  friend ofstream& operator<<(ofstream& f, Partiecomplex& p);
  vector<VortexMur>& getMurVortex()const;
  vector<SmokedMur>& getMurSmoked()const;
  vector<Mur>& getMur()const;

  void action(int positionX, int positionY);
  Element* is_bord_traversable(int positionX, int positionY);
  string to_string()const;
  string print()const;

///////EQUIVALENCES/COMPLEXITE/////////////
int equivalence_mur();
int equivalence_mur_specifique();
///////////////////////////////////////////
bool pastilleSmoked_management(int positionX, int positionY);
bool pastilleVortex_management(int positionX, int positionY);
};
//operateur permettant de formatter la sauvegarde de la partie sur un fichier
inline ofstream& operator<<(ofstream& f, Partiecomplex& p){
  cout << "jean" << endl;
  cout << p.chemin.size() << endl;
  cout << "jean" << endl;
  f << p.chemin;
  f << p.snake;
  f << "eatable" << endl;
  f << p.pastilleEatable;
  f << "smokedp" << endl;
  f << p.pastilleSmoked;
  f << "vortexp" << endl;
  f << p.pastilleVortex;
  f << p.mur;
  f << p.murSmoked;
  f << p.murVortex;
  return f;
}
#endif /* end of include guard: PASTILLECOMPLEX */
