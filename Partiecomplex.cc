#include "Partiecomplex.hh"

Partiecomplex::Partiecomplex(Complexite difficulte):Partie(), pastilleVortex_ready(false), positionX_tete_prec(0), positionY_tete_prec(0){
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
          if(rand() % 100 > equivalence_mur() || flag == 1 || (i == 0 || i == (GAME_SIZE - 1) || j == 0 || j == (GAME_SIZE - 1))){
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
                  if ((rand()%100 < 50)){ //ajout d'un SmokedMur
                    murSmoked.push_back(SmokedMur(i,j));
                  }
                  else{ //ajout d'un VortexMur
                    murVortex.push_back(VortexMur(i,j));
                  }
                }
              }
            }
          }
        }
      flag *= -1; //a la prochaine iteration on ne pourra pas mettre des murs sur la ligne si flag = -1
                  //a la prochaine iteration on pourra mettre des murs sur la ligne si flag = 1
    }

    placeElement(chemin);
    placeElement(snake);
    placeElement(murVortex);
    placeElement(murSmoked);
    placeElement(mur);
    set_new_Pastille(pastilleEatable);
    set_new_Pastille(pastilleSmoked);
    set_new_Pastille(pastilleVortex);
}

Partiecomplex::~Partiecomplex(){}

const Partiecomplex::vector<VortexMur>& getMurVortex()const{ return this->murVortex; }
const Partiecomplex::vector<SmokedMur>& getMurSmoked()const{ return this->murSmoked; }
const Partiecomplex::vector<Mur>& getMur()const{ return this->mur; }
/////////////AFFICHAGES/////////////////////////
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
////////////////////////////////////////////////
///////GESTION/DU/JEU////////////////////////

void Partiecomplex::action(int positionX, int positionY){
  Element* elementSuivant = is_movement_possible(positionX, positionY);
  if(elementSuivant == NULL)
    return; //si le mouvement est impossible, on ne fait rien
  if(!(pastilleEatable_management(positionX, positionY))){ //on verifie si on se deplace sur la pastilleEatable
    if(pastilleSmoked_management(positionX, positionY)){ //on verifie si on se deplace sur la pastilleSmoked ou sur un murSmoked actif
      if(pastilleVortex_management(positionX, positionY))
        deplacer_snake(positionX, positionY); //on deplace juste le snake si le snake n'est pas sur la pastilleEatable
    }
  }
  positionX_tete_prec = positionX;
  positionY_tete_prec = positionY;
  cout << print() << endl;
}
Element* Partiecomplex::is_bord_traversable(int positionX, int positionY){
  return NULL;
}
////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////
//////GESTION/DE/PASTILLE///////////////////////
bool Partiecomplex::pastilleSmoked_management(int positionX, int positionY){
  //en partie simple si la pastille smoke est activee, les bords du jeu deviennent de la fumee et donc traversable
  if(positionX == pastilleSmoked.getX() && positionY == pastilleSmoked.getY()){
    pastilleSmoked_ready = true; //on indique au reste du programme que la pastilleSmoked est activee
    pastilleSmoked.activate(murSmoked); //on change l'affichage des murSmoked
    set_new_Pastille(pastilleSmoked); //on met a jour la position de la pastille sur une nouvelle position
    return true; //le snake n'est pas sur un murSmoked
  }
  if(is_SmokedMur(matrixGame[positionX][positionY]) && pastilleSmoked_ready == true){
    pastilleSmoked_ready = false;
    pastilleSmoked.disable(murSmoked);
    //on deplace le snake sur le chemin apres le murSmoked
    deplacer_snake((2 * positionX - positionX_tete_prec), (2 * positionY - positionY_tete_prec));
    return false; //le snake est sur un murSmoked actif
  }
  return true; //le snake n'est pas sur un murSmoked
}
bool Partiecomplex::pastilleVortex_management(int positionX, int positionY){
  //en partie simple si la pastille smoke est activee, les bords du jeu deviennent de la fumee et donc traversable
  if(positionX == pastilleVortex.getX() && positionY == pastilleVortex.getY()){
    pastilleVortex_ready = true; //on indique au reste du programme que la pastilleVortex est activee
    pastilleVortex.activate(murVortex); //on change l'affichage des murVortex
    set_new_Pastille(pastilleVortex); //on met a jour la position de la pastille sur une nouvelle position
    return true; //le snake n'est pas sur un murVortex
  }

  if(is_VortexMur(matrixGame[positionX][positionY]) && pastilleVortex_ready == true){
    pastilleVortex_ready = false;
    pastilleVortex.disable(murVortex);
    VortexMur* m = dynamic_cast<VortexMur*>(matrixGame[positionX][positionY]);
    //on deplace le snake sur le chemin apres le murVortex
    deplacer_snake(&(m->teleportation(chemin)));
    return false; //le snake est sur un murVortex actif
  }
  return true; //le snake n'est pas sur un murVortex
}
////////////////////////////////////////////////
