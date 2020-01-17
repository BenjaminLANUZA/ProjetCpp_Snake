#include "Snake.hh"

using namespace std;

volatile char direction;
volatile bool jeu_en_cours; //false quand partie finie
volatile int init_autorisee; //-1 non 0 et 1 oui 2 init effectuee
volatile bool jeu_autorise; //quand action a faire vaut true
volatile int difficulte
volatile char type_partie; //si s alors partiesimple, si c alors Partiecomplex
int& nbPoints_snake;

Partiesimple* ps;
Partiecomplex* pc;

int main(){
  action_autorisee = false;
  init_autorisee = -1;
  jeu_en_cours = true;
  ps = NULL;
  pc = NULL;

  thread jeu_fonctionnement (snake); //je crois que ca marche comme ca
  while(jeu_en_cours){
    //affichage graphique
    //RESPECTER L ORDRE DES INSTRUCTIONS
    // demander si l'utilisateur veut reprendre son ancienne partie ou non
    //si il veut pas, afficher les Regles
    //  print_rules();
    //  et demander quelle genre de partie faire
    //    si partie simple mettre type_partie = 's' & mettre init_partie = 1
    //    si partie complexe mettre type_partie = 'c'
    //      & demander quel difficulte & remplir la difficulte cout << "Quel niveau voulez-vous ?" << endl;
    //      cout << "1 - easy  2 - medium  3 hard" << endl;
    //      difficulte = choix utilisateur (1,2 ou3) & mettre init_partie = 1
    // si il veut recuperer son ancienne partie mettre init_autorisee a 0;

    //et apres pour l'affichage faire
    /*
    if(type_partie == 's')
      *ps.getChemin() etc etc PAS DE MURS SMOKEDMUR VORTEXMUR ici
      et affichage pour chaque element en faisant un getX et getY
    else
      *pc.getChemin() etc etc

    exemple
    for(Chemin c : ps->getChemin()){
      afficher un chemin a la position (c.getX(), c.getY())
    }
  }
    */

//LES DEPLACMENTS DU JOUEUR SONT A ENREGISTRER DANS direction sous la forme
  // direciton 'z' haut, 'w' bas, 'd' droite, 'q' gauche

    //ensuite quand le joueur clique sur un bouton ou fait une action (deplacer le snake)
    //tu dois mettre
    //action autorisee a true

  }

  return 0;
}

void snake(){
  do{
    if(init_autorisee == 1 || init_autorisee == 0){ //autorise a initialiser la partie
      init_partie();
    }
    else{
      if(init_autorisee == 2 && action_autorisee){ //si initialisation faite
        if(type_partie == 's')
          jeu_en_cours = ps->jeu(direction, nbPoints_snake);
        else
          jeu_en_cours = pc->jeu(direction, nbPoints_snake);
        action_autorisee = false; //on indique qu on vient de finir l aciton
      }
    }
  }while(jeu_en_cours);

  cout << "Vous avez quitté le jeu" << endl;
  cout << "Votre nbPoints_snake : " << nbPoints_snake << endl;
  store_data(nbPoints_snake);
  //on desalloue la memoire
  delete(ps);
  delete(pc);
}

void init_partie(){
  string n = "";

  if(init_autorisee == 0){
    ifstream file_previous_game("./data/user.txt");

    if(file_previous_game.is_open()){
      char choix;
      getline(file_previous_game, n);
      nbPoints_snake = stoi(n);
      if(n != "") //cas ou il existe une partie precedente
        set_last_game(file_previous_game);
    }
    file_previous_game.close();
  }
  if(n == "" || (init_autorisee == 1)){
    start_new_game();
  }

  init_autorisee = 2; //on indique que l'initialisation est faite
}

void print_rules(){
  //affichage des regles du jeu
  ifstream f("./data/Regles.txt");
  if(f.is_open())
    cout << f.rdbuf();
  f.close();
}
//on choisit le mode de jeu que l'on veut faire, ainsi que les differents niveaux
void start_new_game(){
    switch(type_partie){
      case 's':
        ps = new Partiesimple();
        cout << ps->print() << endl;
        return;
        break;
      case 'c':
        return choose_difficulty();
        break;
      default:
        break;
    }
}
void choose_difficulty(){
  switch(difficulte){
    case 2:
      pc = new Partiecomplex(medium);
      break;
    case 3:
      pc = new Partiecomplex(hard);
      break;
    default:
      //par default on cree une partie easy
      pc = new Partiecomplex(easy);
      break;
  }
  cout << pc->print() << endl;
  return;
}


//on cree/modifie le fichier user.txt pour stocker les donnees formatees pour etre
//reutilisables pour recreer la meme partie lors de la prochaine execution du jeu
void store_data()const{
  ofstream file_nbPoints_snake;
  file_nbPoints_snake.open("./data/user.txt", file_nbPoints_snake.out | file_nbPoints_snake.trunc);
  if(file_nbPoints_snake.is_open()){
    file_nbPoints_snake << nbPoints_snake << endl; //on sauvegarde le nbPoints_snake precedent
    if(ps != NULL){ //ps != NULL => on vient de faire une Partiesimple
      save_partie_simple(file_nbPoints_snake);
    }
    else{ //ps == NULL => on vient de faire une Partiecomplex
      save_partie_complexe(file_nbPoints_snake);
    }
  }
  file_nbPoints_snake.close();
}
void save_partie_simple(ofstream& f)const{
  f << "ps" << endl;
  f << *ps << endl;
}
void save_partie_complexe(ofstream& f)const{
  f << "pc" << endl;
  f << *pc << endl;
}


//On va recreer la partie precedente a partir des donnes sauvegardees dans user.txt
void set_last_game(ifstream& f){
  string n;
  getline(f,n);
  if(n == "ps"){ //Partiesimple
    type_partie = 's';
    return set_partie_simple(f);
  }
  type_partie = 'c';
  return set_partie_complexe(f); //Partiecomplex
}
void set_partie_simple(ifstream& f){
  vector<Chemin> c = set_chemin(f);
  vector<Body> b = set_snake(f);
  EatablePastille e = set_eatablepastille(f);
  SmokedPastille s = set_smokedpastille(f);
  VortexPastille v = set_vortexpastille(f);
  ps = new Partiesimple(c,b,e,s,v,nbPoints_snake);
  cout << ps->print() << endl;
  return;
}
void set_partie_complexe(ifstream& f){
  vector<Chemin> c = set_chemin(f);
  vector<Body> b = set_snake(f);
  EatablePastille e = set_eatablepastille(f);
  SmokedPastille s = set_smokedpastille(f);
  VortexPastille v = set_vortexpastille(f);
  vector<Mur> m = set_mur(f);
  vector<SmokedMur> sm = set_smokedmur(f);
  vector<VortexMur> vm = set_vortexmur(f);
  pc = new Partiecomplex(c,b,m,sm,vm,e,s,v,nbPoints_snake);
  cout << pc->print() << endl;
  return;
}
///////////RECUPERE/LE/CONTENU/DU/FICHIER/user.txt/POUR/RECREER/LA/PARTIE/PRECEDENTE////////
//on va parcourir le fichier user.txt entre 2 bornes definies selon la donnee que l'on cherche a extraire,
//on va extraire cette donne et recreer un groupe d'element du jeu : snake, chemins, murs, pastilles...
vector<Chemin> set_chemin(ifstream& f)const{
  vector<Chemin> chemin;
  string n;
  getline(f, n);
  do{
    getline(f, n);
    if(n == "snake")
      break;
    chemin.push_back(Chemin(positionX(n), positionY(n)));
  }while(n != "snake");
  return chemin;
}
vector<Body> set_snake(ifstream& f)const{
  vector<Body> snake;
  string n;
  do{
    getline(f, n);
    if(n == "eatable")
      break;
    snake.push_back(Body(positionX(n), positionY(n)));
  }while(n != "eatable");
  return snake;
}
EatablePastille set_eatablepastille(ifstream& f)const{
  EatablePastille e;
  string n;
  /*do{
    getline(f, n);
    cout << n << endl;
  }while(n!= "eatable");*/
  getline(f, n);
  return EatablePastille(positionX(n), positionY(n));
}
SmokedPastille set_smokedpastille(ifstream& f)const{
  SmokedPastille s;
  string n;
  do{
    getline(f, n);
  }while(n!= "smokedp");
  getline(f, n);
  return SmokedPastille(positionX(n), positionY(n));
}
VortexPastille set_vortexpastille(ifstream& f)const{
  VortexPastille v;
  string n;
  do{
    getline(f, n);
  }while(n != "vortexp");
  getline(f, n);
  return VortexPastille(positionX(n), positionY(n));
}
vector<Mur> set_mur(ifstream& f)const{
  vector<Mur> mur;
  string n;
  do{
    getline(f, n);
  }while(n != "mur");
  do{
    getline(f, n);
    if(n == "smoked")
      break;
    mur.push_back(Mur(positionX(n), positionY(n)));
  }while(n != "smoked");
  return mur;
}
vector<SmokedMur> set_smokedmur(ifstream& f)const{
  vector<SmokedMur> murs;
  string n;
  do{
    getline(f, n);
    if(n == "vortex")
      break;
    murs.push_back(SmokedMur(positionX(n), positionY(n)));
  }while(n != "vortex");
  return murs;
}
vector<VortexMur> set_vortexmur(ifstream& f)const{
  vector<VortexMur> mur;
  string n;
  while(!f.eof()){
    getline(f, n);
    if(n == "")
      break;
    mur.push_back(VortexMur(positionX(n), positionY(n)));
  }
  return mur;
}

int positionX(const string& s)const{
  string delim(" ");
  string x = s.substr(0, s.find(delim));
  return (stoi(x));
}
int positionY(const string& s)const{
  string delim(" ");
  string y = s.substr(s.find(delim) + 1, s.size() - 1);
  return (stoi(y));
}
////////////////////////////////////////////////////////////////////////////////////////////
