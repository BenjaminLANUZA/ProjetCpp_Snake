#include "Partiecomplex.hh"

Partiecomplex::Partiecomplex(Complexite difficulte):Partie(){
  char flag = -1; //flag permettant de ne pas mettre de murs sur 2 lignes consecutives => les murs ne doivent pas bloquer le jeu en formant une barriere
  complexite = difficulte;
  srand(time(0));
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
          if(rand() % 100 > equivalence_mur() || flag == 1){
            //ajout d'un chemin
            chemin.push_back(Chemin(i,j));
          }
          else{
            //ajout d'un mur : mur, SmokedMur, VortexMur
              if(rand() % 100 < equivalence_mur_specifique()){
                //ajout d'un mur
                mur.push_back(Mur(i,j));
              }
              else{
                  if ((rand()%100 < 50) || chemin.empty()){ //ajout d'un SmokedMur
                    murSmoked.push_back(SmokedMur(i,j));
                  }
                  else{ //ajout d'un VortexMur
                    vector<Chemin>::iterator it;
                    it = chemin.begin() + find_rand_chemin();
                    murVortex.push_back(VortexMur(i,j, *it));
                  }
                }
              }
            }
          }
        }
      flag *= -1; //a la prochaine iteration on ne pourra pas mettre des murs sur la ligne si flag = -1
                  //a la prochaine iteration on pourra mettre des murs sur la ligne si flag = 1
    }
    placeElement(murVortex);
    placeElement(murSmoked);
    placeElement(mur);
    placeElement(chemin);
    placeElement(snake);
    set_new_Pastille(pastilleEatable);
    //set_new_Pastille(pastilleSmoked);
    //set_new_Pastille(pastilleVortex);
}

Partiecomplex::~Partiecomplex(){}

Element* Partiecomplex::is_movement_possible(int positionX, int positionY){
  if(is_bord(positionX, positionY))
    return NULL;
  if((matrixGame[positionX][positionY])->is_traversable())
  //A MODIFIER/////////////////////////////////////////////////////////////////////////////////////////
    return matrixGame[positionX][positionY]; //si traversable on peut se deplacer
  return NULL; //si on element pas traversable, on ne peut pas se deplacer
}

void Partiecomplex::action(int positionX, int positionY){
  Element* elementSuivant = is_movement_possible(positionX, positionY);
  if(elementSuivant == NULL)
    return; //si le mouvement est impossible, on ne fait rien
  if(!(pastilleEatable_management(positionX, positionY))) //on verifie si on se deplace sur la pastilleEatable
    deplacer_snake(positionX, positionY); //on deplace juste le snake si le snake n'est pas sur la pastilleEatable
  cout << print() << endl;
}
int Partiecomplex::equivalence_mur(){
  //retourne la probablite / 100 de creer un mur (general)
  switch(this->complexite){
    case easy:  //probabilite
      return 10;//10 / 100 mur
      break; // 90 /100 chemin
    case hard :  //probabilite
      return 30;//30 / 100 mur
      break; // 70 /100 chemin
    default: //medium   //probabilite
      return 15;//15 / 100 mur
      break; // 85 /100 chemin
  }
}
int Partiecomplex::equivalence_mur_specifique(){
  //on retourne la probabilite / 100 de creer un mur normal
  switch(this->complexite){
    case easy:  //probabilite
      return 10;//10 / 100 mur normal
      break; // 45 /100 SmokedMur ; 45 / 100 VortexMur
    case hard :  //probabilite
      return 50;//50 / 100 mur normal
      break; // 25 /100 SmokedMur ; 25 / 100 VortexMur
    default: //medium   //probabilite
      return 30;//30 / 100 mur normal
      break; // 35 /100 SmokedMur ; 35 / 100 VortexMur
  }
}
int Partiecomplex::equivalence_temporelle(){
  //on retourne la probabilite / 100 de creer un mur normal
  switch(this->complexite){
    case easy:  //probabilite
      return 10;//10 / 100 mur normal
      break; // 45 /100 SmokedMur ; 45 / 100 VortexMur
    case hard :  //probabilite
      return 50;//50 / 100 mur normal
      break; // 25 /100 SmokedMur ; 25 / 100 VortexMur
    default: //medium   //probabilite
      return 30;//30 / 100 mur normal
      break; // 35 /100 SmokedMur ; 35 / 100 VortexMur
  }
}


string Partiecomplex::print()const{
  string t[GAME_SIZE_PRINT][GAME_SIZE_PRINT];
  printVector(t, mur);
  printVector(t, murVortex);
  printVector(t, murSmoked);
  return printTab(t);
}
string Partiecomplex::to_string()const{
  string t[GAME_SIZE_PRINT][GAME_SIZE_PRINT];
  to_stringVector(t, mur);
  to_stringVector(t, murVortex);
  to_stringVector(t, murSmoked);
  return to_stringTab(t);
}
