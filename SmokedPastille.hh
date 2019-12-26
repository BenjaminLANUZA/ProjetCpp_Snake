#ifndef SMOKEDPASTILLE
#define SMOKEDPASTILLE
#include <vector>
#include "Pastille.hh"

class SmokedPastille:public Pastille{

public:
  SmokedPastille():Pastille(){};
  SmokedPastille(int positionX, int positionY):Pastille(positionX, positionY){}
  SmokedPastille(const SmokedPastille& s):Pastille(s.getX(),s.getY()){}
  SmokedPastille(const Chemin& c):Pastille(c){}
  ~SmokedPastille(){}

  string to_string()const{
    stringstream s;
    s << "Pastille smoked - position x " << x << " ; y " << y << endl;
    return s.str();
  }
  string print()const{ return "s"; }

  /*void action(vector<const SmokedMur&> mursmoked)const{
    for(const SmokedMur& smoke : mursmoked){
      smoke.activate();
    }
  };

  void disable(vector<const SmokedMur&> mursmoked)const{
    for(const SmokedMur& smoke : mursmoked){
      smoke.desactivate();
    }
  };*/

};

#endif /* end of include guard: SMOKEDPASTILLE */
