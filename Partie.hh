#ifndef PARTIE
#define PARTIE

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
//#include <typeinfo>
#include <iterator>
#include <algorithm>
#include <ctime>

using namespace std;

#include "Element.hh"
////////MUR/////////
#include "Mur.hh" //mur normal
#include "SmokedMur.hh" //mur traversable quand une certaine pastille est mangee
#include "VortexMur.hh" //mur de teleportation quand une certaine pastille est mangee
////Pastille///////
#include "Pastille.hh" //classe abstraite
#include "SmokedPastille.hh" //pastille activant les murs smoked
#include "EatablePastille.hh" //pastille faisant grandir le snake quand il la mange
#include "SmokedPastille.hh" //pastille rendant transformant les murs en fumee et donc traversable
#include "VortexPastille.hh" //pastille activant les murs vortex
///////SNAKE///////
#include "Tete.hh"
#include "Body.hh"
////CHEMIN////////
#include "Chemin.hh"

using namespace std;
class Partie{
protected :
  Element*** matrixGame;
  vector<Body> snake;
  vector<Chemin> chemin;
  EatablePastille pastilleEatable;
  SmokedPastille pastilleSmoked;
  VortexPastille pastilleVortex;
  static constexpr int GAME_SIZE = 15;
  static constexpr int GAME_SIZE_PRINT = GAME_SIZE + 2;
  //ces flag changeront a des intervalles de temps differents en concurrence
  //du rest du programme => utilisation de thread et de volatil pour etre sur d'aller
  //chercher la valeur dans la memoire et non dans le cache
  bool pastilleSmoked_ready;
  bool game; //indique si une partie est finie ou non
  int nbPoints;


public:
  Partie():pastilleSmoked_ready(false),game(true),nbPoints(0){
    matrixGame = new Element**[GAME_SIZE];
    for(int i = 0; i < GAME_SIZE; i++){
      matrixGame[i] = new Element*[GAME_SIZE];
      }
  }
  Partie(vector<Chemin>& c, vector<Body>& b, EatablePastille& e, SmokedPastille& s, VortexPastille& v, int& score):snake(b),chemin(c),pastilleEatable(e),pastilleSmoked(s),pastilleVortex(v),pastilleSmoked_ready(false),game(true),nbPoints(score){
    matrixGame = new Element**[GAME_SIZE];
    for(int i = 0; i < GAME_SIZE; i++){
      matrixGame[i] = new Element*[GAME_SIZE];
      }
    placeElement(snake);
    placeElement(chemin);
    set_new_Pastille(pastilleEatable);
    set_new_Pastille(pastilleSmoked);
    set_new_Pastille(pastilleVortex);
  }
  virtual ~Partie(){
    for(int i = 0; i < GAME_SIZE; i++){
      delete[] matrixGame[i];
    }
    delete[] matrixGame;
  }
  //accesseurs
  const int& getNbPoints()const;
  const vector<Chemin>& getChemin()const;
  const vector<Body>& getSnake()const;
  const EatablePastille& getEatablePastille()const;
  const SmokedPastille& getSmokedPastille()const;
  const VortexPastille& getVortexPastille()const;
  //operateurs permettants de formatter la sauvegarde d'un groupe d'element sur un fichier
  friend ofstream& operator<<(ofstream& f, vector<Chemin>& v);
  friend ofstream& operator<<(ofstream& f, vector<Body>& v);
  friend ofstream& operator<<(ofstream& f, vector<Mur>& v);
  friend ofstream& operator<<(ofstream& f, vector<SmokedMur>& v);
  friend ofstream& operator<<(ofstream& f, vector<VortexMur>& v);
  ////////////////////////////////////////////////
  /////////////AFFICHAGES/////////////////////////
  virtual string to_string()const = 0;
  virtual string print()const{return "";};
  void print_bord(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const;
  void printSnake(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const;
  string printTab(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const;
  void to_stringSnake(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const;
  string to_stringTab(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const;
  void print_Transparence()const{
    for(int i = 0; i < GAME_SIZE; i++){
      for(int j = 0; j < GAME_SIZE; j++){
        cout << (matrixGame[i][j])->is_traversable();
      }
      cout << endl;
    }
    cout << endl;
  }
  template<typename T>
  void printVector(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT], const vector<T>& vect)const{
    typename vector<T>::const_iterator it;
    for(it = vect.begin(); it != vect.end(); it++){
      //cout << "impression " << it->print() << endl;
      tabPrint[it->getX() + 1][it->getY() + 1] = it->print();
    }
  }
  template<typename T>
  void to_stringVector(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT], const vector<T>& vect)const{
    typename vector<T>::const_iterator it;
    for(it = vect.begin(); it != vect.end(); it++){
      tabPrint[it->getX() + 1][it->getY() + 1] = it->to_string();
    }
  }
  ////////////////////////////////////////////////
  //////GESTION/DE/PASTILLE///////////////////////
  int find_rand_chemin()const;
  template<typename T>
  void set_new_Pastille(T& pastille){ //cree une pastille
    vector<Chemin>::const_iterator it;
    it = this->chemin.begin() + find_rand_chemin();
    pastille = T(*it);
  }
  bool pastilleEatable_management(int positionX, int positionY);
  virtual bool pastilleSmoked_management(int positionX, int positionY){return false;}
  virtual bool pastilleVortex_management(int positionX, int positionY){return false;}
  ////////////////////////////////////////////////
   /////////identificateurs d'Element/////////////
  bool is_Chemin(Element* e)const{ return (dynamic_cast<Chemin*>(e) != NULL); }
  bool is_VortexMur(Element* e)const{ return (dynamic_cast<VortexMur*>(e) != NULL); }
  bool is_SmokedMur(Element* e)const{ return (dynamic_cast<SmokedMur*>(e) != NULL); }
  bool is_Body(Element* e)const{ return (dynamic_cast<Body*>(e) != NULL); }
  //////////////////////////////////////////////
  ///////GESTION/DU/JEU////////////////////////
  bool jeu(char direction, int& nbPoints_snake);
  virtual void action(int positionX, int positionY){} //definit le comportement du jeu en fonction des differents types de parties
  virtual Element* is_bord_traversable(int positionX, int positionY){return NULL;}
  Element* is_movement_possible(int positionX, int positionY);
  bool is_bord(int positionX, int positionY);
  void erase_chemin(int positionX, int positionY);
  Element* lose();
  template<typename T>
  void placeElement(vector<T>& vect)const{
    typename vector<T>::iterator it;
    for(it = vect.begin(); it != vect.end(); it++){
      matrixGame[it->getX()][it->getY()] = &(*it);
    }
  }
  ///////GESTION/SNAKE/////////////////////////
  Element* deplacer_snake(int positionX, int positionY);
  Element* deplacer_snake(Element* e);
  void add_body_to_snake(int positionX, int positionY);
  bool is_snake_part(int positionX, int positionY);
  //////////////////////////////////////////////
};

//operateurs permettants de formatter la sauvegarde d'un groupe d'element sur un fichier
inline ofstream& operator<<(ofstream& f, vector<Chemin>& v){
  f << "chemin" << endl;
  for(Chemin& element : v){
    f << element;
  }
  return f;
}
inline ofstream& operator<<(ofstream& f, vector<Body>& v){
  f << "snake" << endl;
  for(Body& element : v){
    f << element;
  }
  return f;
}

inline ofstream& operator<<(ofstream& f, vector<Mur>& v){
  f << "mur" << endl;
  for(Mur& element : v){
    f << element;
  }
  return f;
}
inline ofstream& operator<<(ofstream& f, vector<SmokedMur>& v){
  f << "smoked" << endl;
  for(SmokedMur& element : v){
    f << element;
  }
  return f;
}
inline ofstream& operator<<(ofstream& f, vector<VortexMur>& v){
  f << "vortex" << endl;
  for(VortexMur& element : v){
    f << element;
  }
  return f;
}

#endif /* end of include guard: PARTIE */
