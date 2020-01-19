#ifndef VORTEXPASTILLE
#define VORTEXPASTILLE
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Pastille.hh"
class VortexPastille:public Pastille{
public:
  VortexPastille():Pastille(){srand(time(0));
     (this->texture).loadFromFile("images/Pastilles/Vortex_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    }
  VortexPastille(int positionX, int positionY):Pastille(positionX, positionY){srand(time(0));
   (this->texture).loadFromFile("images/Pastilles/Vortex_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(positionX*64.f,positionY*64.f);}
    
  VortexPastille(const VortexPastille& v):Pastille(v.getX(),v.getY()){srand(time(0));
  (this->texture).loadFromFile("images/Pastilles/Vortex_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
    (this->sprite).setPosition(v.getX()*64.f,v.getY()*64.f);}

  VortexPastille(const Chemin& c):Pastille(c){srand(time(0));
  (this->texture).loadFromFile("images/Pastilles/Vortex_Pastille.png", sf::IntRect(0, 0, 63, 63));
    (this->sprite).setTexture(this->texture);
 }
  ~VortexPastille(){}

  string to_string()const{
    stringstream s;
    s << "Pastille Vortex - position x " << x << " ; y " << y << endl;
    return s.str();
  }
  string print()const{ return "x"; }

  Chemin& activate(vector<Chemin>& c){
    //seule la pastille sait sur quel chemin un element va se teleporte
    return c[(rand() % ((int)c.size() - 1))];
  }

  void activate(vector<VortexMur>& murvortex){
    for(VortexMur& v : murvortex){
      v.activate();
    }
  }

  void disable(vector<VortexMur>& murvortex){
      for(VortexMur& v : murvortex){
        v.desactivate();
      }
  }

};

#endif /* end of include guard: VORTEXPASTILLE */
