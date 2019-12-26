#ifndef VORTEXPASTILLE
#define VORTEXPASTILLE
#include <vector>
#include "Pastille.hh"
class VortexPastille:public Pastille{
public:
  VortexPastille():Pastille(){};
  VortexPastille(int positionX, int positionY):Pastille(positionX, positionY){}
  VortexPastille(const VortexPastille& v):Pastille(v.getX(),v.getY()){}
  VortexPastille(const Chemin& c):Pastille(c){}
  ~VortexPastille(){}

  string to_string()const{
    stringstream s;
    s << "Pastille Vortex - position x " << x << " ; y " << y << endl;
    return s.str();
  }
  string print()const{ return "x"; }
/*
  vector<const Chemin&> action(vector<const VortexMur&> murvortex)const{
    vector<const Chemin&> teleportation;
    for(const VortexMur& v : murvortex){
      teleportation.push_back(v.activate());
    }
    return teleportation;
  };

  void disable(vector<const VortexMur&> murvortex){
      for(VortexMur v : murvortex){
        v.desactivate();
      }
  };*/

};

#endif /* end of include guard: VORTEXPASTILLE */
