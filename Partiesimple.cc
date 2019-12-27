#include "Partiesimple.hh"
Partiesimple::Partiesimple():Partie(){
  for(int i = 0; i < GAME_SIZE; i++){
    for(int j = 0; j < GAME_SIZE; j++){
      if(i == 0 && j == 0){
        snake.push_back(Tete(i,j));
      }
      else{
        if(i == 0 && j == 1){
        snake.push_back(Body(i,j));
        }
        else{
          chemin.push_back(Chemin(i,j));
        }
      }
    }
  }
  placeElement(snake);
  placeElement(chemin);
  set_new_Pastille(pastilleEatable);
  set_new_Pastille(pastilleSmoked);
  set_new_Pastille(pastilleVortex);
}

Partiesimple::~Partiesimple(){}
/////////////AFFICHAGES/////////////////////////
string Partiesimple::to_string()const{
  string t[GAME_SIZE_PRINT][GAME_SIZE_PRINT];
  return to_stringTab(t);
}
string Partiesimple::print()const{
  string t[GAME_SIZE_PRINT][GAME_SIZE_PRINT];
  return printTab(t);
}
////////////////////////////////////////////////
///////GESTION/DU/JEU////////////////////////
void Partiesimple::action(int positionX, int positionY){
  Element* elementSuivant = is_movement_possible(positionX, positionY);
  if(elementSuivant == NULL)
    return; //si le mouvement est impossible, on ne fait rien
  //si pastilleSmoked activee et qu'on est sur un bord
  if(pastilleSmoked_ready == true && is_bord(positionX, positionY)){
    deplacer_snake(elementSuivant); // on deplace le snake sur la position suivante
    pastilleSmoked_ready = false; //on desactive la fonction smoke)
  }
  else{
    pastilleSmoked_management(positionX, positionY);
    if(!(pastilleVortex_management(positionX, positionY))){ //on verifie si on est sur une pastille
      if(!(pastilleEatable_management(positionX, positionY))) //on verifie si on se deplace sur la pastilleEatable
        deplacer_snake(positionX, positionY); //on deplace juste le snake si le snake n'est pas sur la pastilleEatable
    }
  }
  cout << print() << endl;
}
Element* Partiesimple::is_bord_traversable(int positionX, int positionY){
  if(pastilleSmoked_ready == true){
    return define_next_position_smoked(positionX, positionY);
  }
  return NULL;
}
////////////////////////////////////////////////
//////GESTION/DE/PASTILLE///////////////////////
bool Partiesimple::pastilleSmoked_management(int positionX, int positionY){
  //en partie simple si la pastille smoke est activee, les bords du jeu deviennent de la fumee et donc traversable
  if(positionX == pastilleSmoked.getX() && positionY == pastilleSmoked.getY()){
    pastilleSmoked_ready = true; //on indique au reste du programme que la pastilleSmoked est activee
    set_new_Pastille(pastilleSmoked); //on met a jour la position de la pastille sur une nouvelle position
    return true; //le snake est sur la pastilleSmoked
  }
  return false; //le snake n'est pas sur la pastilleSmoked
}
bool Partiesimple::pastilleVortex_management(int positionX, int positionY){
  //en partie simple si la pastille smoke est activee, les bords du jeu deviennent de la fumee et donc traversable
  if(positionX == pastilleVortex.getX() && positionY == pastilleVortex.getY()){
    deplacer_snake(define_next_position_vortex());
    set_new_Pastille(pastilleVortex); //on met a jour la position de la pastille sur une nouvelle position
    return true; //le snake est sur la pastilleSmoked
  }
  return false; //le snake n'est pas sur la pastilleSmoked
}
Element* Partiesimple::define_next_position_smoked(int positionX, int positionY){
  switch(positionX){
    case -1:
      return matrixGame[GAME_SIZE - 1][positionY];
      break;
    case GAME_SIZE:
      return matrixGame[0][positionY];
      break;
    default:
      switch(positionY){
        case -1:
          return matrixGame[positionX][GAME_SIZE - 1];
          break;
        case GAME_SIZE:
          return matrixGame[positionX][0];
          break;
        default:
          return NULL;
          break;
      }
      break;
  }
}
Element* Partiesimple::define_next_position_vortex(){
  Chemin& c = pastilleVortex.activate(chemin); //seule la pastille a la droit de determiner sur quel chemin se teleporte
  return matrixGame[c.getX()][c.getY()];
}
////////////////////////////////////////////////
