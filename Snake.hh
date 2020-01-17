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
  void store_data();
  void save_partie_simple(ofstream& f);
  void save_partie_complexe(ofstream& f);
  ////////////////////////////////////////
  //////////INITIE/LA/RECREATION/DE/LA/PARTIE/PRECEDENTE////////////
  void set_last_game(ifstream& f);
  void set_partie_simple(ifstream& f);
  void set_partie_complexe(ifstream& f);
  ////////////////////////////////////////////////////////////////////////////////////////////
  ///////////RECUPERE/LE/CONTENU/DU/FICHIER/user.txt/POUR/RECREER/LA/PARTIE/PRECEDENTE////////
  vector<Body> set_snake(ifstream& f);
  vector<Chemin> set_chemin(ifstream& f);
  vector<Mur> set_mur(ifstream& f);
  vector<SmokedMur> set_smokedmur(ifstream& f);
  vector<VortexMur> set_vortexmur(ifstream& f);
  EatablePastille set_eatablepastille(ifstream& f);
  VortexPastille set_vortexpastille(ifstream& f);
  SmokedPastille set_smokedpastille(ifstream& f);
  int positionX(const string& s);
  int positionY(const string& s);
  ////////////////////////////////////////////////////////////////////////////////////////////
  template <typename T>
  void register_vector(ofstream& f, const vector<T>& vect){
    typename vector<T>::const_iterator it;
    for(it = vect.begin(); it != vect.end(); it++){
      f << it->getX() << " " << it->getY() << endl;
    }
  }

#endif /* end of include guard: SNAKE */
