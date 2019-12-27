#ifndef SMOKEDMUR
#define SMOKEDMUR
#include "Mur.hh"

using namespace std;
//SmokedMur est un mur qui lorsqu un certains type de pastille est mange par le
//serpent, certains murs se transforment en SmokedMur et le serpent peut passer
//au travers
class SmokedMur : public Mur{
  protected:
  string print_mur_specifique;

  public :
  SmokedMur(int positionX, int positionY):Mur(positionX, positionY),print_mur_specifique("="){}
  SmokedMur(const SmokedMur& s):Mur(s.getX(),s.getY()),print_mur_specifique("="){}
  ~SmokedMur(){}

  string to_string()const{ return "SmokedMur"; }
  string print()const{ return this->print_mur_specifique; }
  //permet de definir l aspect traversable ou non d un tel mur
  void activate(){
    this->traversable = true;
    this->print_mur_specifique = "~";}
  void desactivate(){
    this->traversable = false;
    this->print_mur_specifique = "=";}
};

#endif /* end of include guard: SMOKEDMUR */
