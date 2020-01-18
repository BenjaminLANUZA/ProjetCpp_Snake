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

  string to_string()const{ return "Pastille smoked"; }
  string print()const{ return "s"; }

  void activate(vector<SmokedMur>& mursmoked){
    for(SmokedMur& smoke : mursmoked){
      smoke.activate();
    }
  }

  void disable(vector<SmokedMur>& mursmoked){
    for(SmokedMur& smoke : mursmoked){
      smoke.desactivate();
    }
  }

};

#endif /* end of include guard: SMOKEDPASTILLE */
