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
#include <chrono>
#include <thread>

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
  static constexpr int GAME_SIZE = 15;
  static constexpr int GAME_SIZE_PRINT = GAME_SIZE + 2;
  //ces flag changeront a des intervalles de temps differents en concurrence
  //du rest du programme => utilisation de thread et de volatil pour etre sur d'aller
  //chercher la valeur dans la memoire et non dans le cache
  volatile bool pastilleSmoked_ready;
  bool game; //indique si une partie est finie ou non


public:
  Partie():pastilleSmoked_ready(false),game(true){}
  virtual ~Partie(){
    for(int i = 0; i < GAME_SIZE; i++){
      delete[] matrixGame[i];
    }
    delete[] matrixGame;
  }

  template<typename T>
  void placeElement(vector<T>& vect)const{
    typename vector<T>::iterator it;
    for(it = vect.begin(); it != vect.end(); it++){
      matrixGame[it->getX()][it->getY()] = &(*it);
    }
  }
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
/*template<typename T>
void set_Pastille(T& pastille){ //place une pastille
  vector<Chemin>::iterator it;
  it = this->chemin.begin() + find_rand_chemin();
  int positionX_prec = it->getX();
  int positionY_prec = it->getY();
  (it)->setPosition(pastille); //on place le chemin a l'ancienne position de la pastille
  matrixGame[pastille.getX()][pastille.getY()] = &(*it); //on met a jour matrixGame
  pastille.setPosition(it->getX(), it->getY()); //on change la position de la pastille
  matrixGame[pastille.getX()][pastille.getY()] = &pastille; //on met a jour matrixGame
}*/
template<typename T>
void set_new_Pastille(T& pastille){ //cree une pastille
  vector<Chemin>::const_iterator it;
  it = this->chemin.begin() + find_rand_chemin();
  pastille = T(*it);
  //chemin.erase(it); //on supprime le chemmin qui est remplace par la pastille
  //matrixGame[pastille.getX()][pastille.getY()] = &pastille; //on met a jour matrixGame
}
////////////////////////////////////////////////
 /////////identificateurs d'Element/////////////
  bool isChemin(Element* e)const{ return (dynamic_cast<Chemin*>(e) != NULL); }
  bool isVortexMur(Element* e)const{ return (dynamic_cast<VortexMur*>(e) != NULL); }
  bool isSmokedMur(Element* e)const{ return (dynamic_cast<SmokedMur*>(e) != NULL); }
  bool isBody(Element* e)const{ return (dynamic_cast<Body*>(e) != NULL); }
  //////////////////////////////////////////////
  ///////GESTION/DU/JEU////////////////////////
    void jeu();
    virtual void action(int positionX, int positionY){} //definit le comportement du jeu en fonction des differents types de parties
    virtual Element* is_bord_traversable(int positionX, int positionY){return NULL;}
    Element* is_movement_possible(int positionX, int positionY);
    bool is_bord(int positionX, int positionY);
    Element* deplacer_snake(int positionX, int positionY);
    bool pastilleEatable_management(int positionX, int positionY);
    void add_body_to_snake(int positionX, int positionY);
    void erase_chemin(int positionX, int positionY);
};

#endif /* end of include guard: PARTIE */
