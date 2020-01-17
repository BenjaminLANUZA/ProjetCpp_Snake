#ifndef SNAKE
#define SNAKE

#include <iostream>
#include <fstream>
#include <string>
#include <thread>         // std::thread
#include "Partiesimple.hh"
#include "Partiecomplex.hh"

using namespace std;

  void snake();
  void init_partie();
  void print_rules();
  ///////CREE/UNE/NOUVELLE/PARTIE///////
  void start_new_game();
  void choose_difficulty();
  ///////////////////////////////////////
  ///////SAUVEGARDE/LA/PARTIE////////////
  void store_data()const;
  void save_partie_simple(ofstream& f)const;
  void save_partie_complexe(ofstream& f)const;
  ////////////////////////////////////////
  //////////INITIE/LA/RECREATION/DE/LA/PARTIE/PRECEDENTE////////////
  void set_last_game(ifstream& f);
  void set_partie_simple(ifstream& f);
  void set_partie_complexe(ifstream& f);
  ////////////////////////////////////////////////////////////////////////////////////////////
  ///////////RECUPERE/LE/CONTENU/DU/FICHIER/user.txt/POUR/RECREER/LA/PARTIE/PRECEDENTE////////
  vector<Body> set_snake(ifstream& f)const;
  vector<Chemin> set_chemin(ifstream& f)const;
  vector<Mur> set_mur(ifstream& f)const;
  vector<SmokedMur> set_smokedmur(ifstream& f)const;
  vector<VortexMur> set_vortexmur(ifstream& f)const;
  EatablePastille set_eatablepastille(ifstream& f)const;
  VortexPastille set_vortexpastille(ifstream& f)const;
  SmokedPastille set_smokedpastille(ifstream& f)const;
  int positionX(const string& s)const;
  int positionY(const string& s)const;
  ////////////////////////////////////////////////////////////////////////////////////////////
  template <typename T>
  void register_vector(ofstream& f, const vector<T>& vect)const{
    typename vector<T>::const_iterator it;
    for(it = vect.begin(); it != vect.end(); it++){
      f << it->getX() << " " << it->getY() << endl;
    }
  }

#endif /* end of include guard: SNAKE */
