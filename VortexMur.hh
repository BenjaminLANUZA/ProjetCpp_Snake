#ifndef VORTEXMUR
#define VORTEXMUR

#include "SmokedMur.hh"
#include "Chemin.hh"

using namespace std;

class VortexMur : public SmokedMur{
  private :
  const Chemin& teleportation;

  public :
  VortexMur(int positionX, int positionY, const Chemin& tel):SmokedMur(positionX, positionY),teleportation(tel){};
  VortexMur(const VortexMur& v):SmokedMur(v.getX(), v.getY()),teleportation(v.getTeleportation()){};
  ~VortexMur(){};

  const Chemin& getTeleportation()const{ return this->teleportation; };
  string to_string()const{ return "mur vortex"; };
  string print()const{ return print_mur_specifique; };
  //on retourne le mur vers lequel se teleporter
  const Chemin& activate(){
    this->traversable = true;
    this->print_mur_specifique = "@";
    return this->teleportation;
  };
  //a chaque desactivation, le mur vers lequel le vortex pointe change
  void desactivate(){
    this->traversable = false;
    this->print_mur_specifique = "=";
  };
};
#endif /* end of include guard: VORTEXMUR */
