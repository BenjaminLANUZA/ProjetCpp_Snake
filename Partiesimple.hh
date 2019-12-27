#ifndef PARTIESIMPLE
#define PARTIESIMPLE

#include "Partie.hh"

class Partiesimple : public Partie{ //private car on veut etre sur que tous les elements heredite de Partie soient private ici
private:

public:
  Partiesimple();
  Partiesimple(vector<Chemin>& c, vector<Body>& b, EatablePastille& e, SmokedPastille& s, VortexPastille& v, int& score):Partie(c, b, e, s, v, score){}
  ~Partiesimple();
  //operateur permettant de formatter la sauvegarde de la partie sur un fichier
  friend ofstream& operator<<(ofstream& f, Partiesimple& p);
  string to_string()const;
  string print()const;
  void action(int positionX, int positionY);
  Element* is_bord_traversable(int positionX, int positionY);
  bool pastilleSmoked_management(int positionX, int positionY);
  bool pastilleVortex_management(int positionX, int positionY);
  Element* define_next_position_vortex();
  Element* define_next_position_smoked(int positionX, int positionY);
};

//operateur permettant de formatter la sauvegarde de la partie sur un fichier
inline ofstream& operator<<(ofstream& f, Partiesimple& p){
  f << p.chemin;
  f << p.snake;
  f << "eatable" << endl;
  f << p.pastilleEatable;
  f << "smokedp" << endl;
  f << p.pastilleSmoked;
  f << "vortexp" << endl;
  f << p.pastilleVortex;
  return f;
}

#endif /* end of include guard: PARTIESIMPLE */
