#include "Partiesimple.hh"
Partiesimple::Partiesimple():Partie(){
  matrixGame = new Element**[GAME_SIZE];
  for(int i = 0; i < GAME_SIZE; i++){
    matrixGame[i] = new Element*[GAME_SIZE];
    }
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
  //set_new_Pastille(pastilleSmoked);
}

Partiesimple::~Partiesimple(){}

string Partiesimple::to_string()const{
  string t[GAME_SIZE_PRINT][GAME_SIZE_PRINT];
  return to_stringTab(t);
}

string Partiesimple::print()const{
  string t[GAME_SIZE_PRINT][GAME_SIZE_PRINT];
  return printTab(t);
}

void Partiesimple::action(int positionX, int positionY){
  Element* elementSuivant = is_movement_possible(positionX, positionY);
  if(elementSuivant == NULL)
    return; //si le mouvement est impossible, on ne fait rien
  if(!(pastilleEatable_management(positionX, positionY))) //on verifie si on se deplace sur la pastilleEatable
    deplacer_snake(positionX, positionY); //on deplace juste le snake si le snake n'est pas sur la pastilleEatable
  cout << print() << endl;
}
Element* Partiesimple::is_bord_traversable(int positionX, int positionY){
  if(pastilleSmoked_ready == true){
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
  return NULL;
}
