#include "Partiesimple.hh"
#include "Partiecomplex.hh"
#include "Utilities.hh"

/*A AJOUTER
VORTEXMUR DESACTIVATE CHANGE LE VORTEX A CHAQUE APPEL
action et disable des pastilles -> pb de ptr avec les references
*/
int main(){
  Partiesimple a;
  cout << a.print() << endl;
  a.jeu();

  //Partiecomplex b(hard);
  //cout << b.print() << endl;
  //b.jeu();
}
