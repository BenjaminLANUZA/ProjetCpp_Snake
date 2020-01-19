#include "Snake.hh"


sf::RenderWindow window(sf::VideoMode(WINDOW,WINDOW), "Snake 4.0",sf::Style::Titlebar | sf::Style::Close);  

Snake::Snake(){
  int score = -1;//, score_max;
  ps = NULL;
  pc = NULL;
  ifstream file_previous_game("./data/user.txt");
  if(file_previous_game.is_open()){
    char choix;
    string n;
    cout << "Voulez-vous reprendre la ou vous vous etiez arrete ? (y/n)" << endl;
    getline(file_previous_game, n);
    previous_score = stoi(n);
    cout <<  "\n\nVotre ancien score : " << n << endl;
    cin >> choix;
    if(choix == 'y') //cas ou on veut recommencer la ou on s'etait arrete a la partie d'avant
      score = set_last_game(file_previous_game);
  }
  file_previous_game.close();

  if(score == -1) //cas ou on veut creer une nouvelle partie
    score = start_new_game();
  cout << "Vous avez quitté le jeu" << endl;
  cout << "Votre score : " << score << endl;
  store_data(score);
}

Snake::~Snake(){
  //on desalloue la memoire
  delete(ps);
  delete(pc);
}

int Snake::DrawFond(){

    sf::Texture textureFond;
    if (!textureFond.loadFromFile("Chemin.jpg", sf::IntRect(0,0,WINDOW,WINDOW))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteFond(textureFond);

  sf::Texture contour1; 
  if (!contour1.loadFromFile("mur.jpg", sf::IntRect(0,0,WINDOW,TAILLEIMAGE))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour1(contour1);

  sf::Texture contour2; 
  if (!contour2.loadFromFile("mur.jpg", sf::IntRect(0,0,TAILLEIMAGE,WINDOW))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour2(contour2);


  sf::Texture contour3; 
  if (!contour3.loadFromFile("mur.jpg", sf::IntRect(0,0,WINDOW,TAILLEIMAGE))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour3(contour3);
  spriteContour3.setPosition(sf::Vector2f(0, 650.f)); // absolute position

  sf::Texture contour4; 
  if (!contour4.loadFromFile("mur.jpg", sf::IntRect(0,0,TAILLEIMAGE,WINDOW))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour4(contour4);
  spriteContour4.setPosition(sf::Vector2f(1008.f, 0)); // absolute position

  window.draw(spriteFond);
  window.draw(spriteContour1);
  window.draw(spriteContour2);
  window.draw(spriteContour3);
  window.draw(spriteContour4);

  return 0; 
}

//-------------------------------------------------------------------------------------------------------------
void Snake::draw_Game(Partiesimple partie){
     window.clear();
     int v = 0; 
     v = DrawFond();
     if(v){cout<<"Erreur DrawFond"<<endl; }
     
     Element*  ElementMatrice;
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            ElementMatrice = partie.getElementMatrixptr( i,  j);
            window.draw(ElementMatrice->getSprite());


        }
    }
    window.display();
}

void Snake::print_rules(){
  //affichage des regles du jeu
  ifstream f("./data/Regles.txt");
  if(f.is_open())
    cout << f.rdbuf();
  f.close();
}
//on choisit le mode de jeu que l'on veut faire, ainsi que les differents niveaux
int Snake::start_new_game(){
  print_rules();
  int i = DrawFond();
if (!i){
    return EXIT_FAILURE;
  }
  char choix;
  do{
    cin >> choix;
    switch(choix){
      case '1':
        ps = new Partiesimple();
        cout << ps->print() << endl;
        return ps->jeu();
        break;
      case '2':
        cout << "Quel niveau voulez-vous ?" << endl;
        cout << "1 - easy  2 - medium  3 hard" << endl;
        cin >> choix;
        return choose_difficulty(choix);
        break;
      default:
        break;
    }
  }while(choix != 27); //tant que l'utilisateur entre une donnee invalide ou ne quitte pas le jeu
  return -1; //signale une erreur
}
int Snake::choose_difficulty(char& choix){
  switch(choix){
    case '2':
      pc = new Partiecomplex(medium);
      break;
    case '3':
      pc = new Partiecomplex(hard);
      break;
    default:
      //par default on cree une partie easy
      pc = new Partiecomplex(easy);
      break;
  }
  cout << pc->print() << endl;
  return pc->jeu(); //on lance le jeu
}


//on cree/modifie le fichier user.txt pour stocker les donnees formatees pour etre
//reutilisables pour recreer la meme partie lors de la prochaine execution du jeu
void Snake::store_data(int score)const{
  ofstream file_score;
  file_score.open("./data/user.txt", file_score.out | file_score.trunc);
  if(file_score.is_open()){
    file_score << score << endl; //on sauvegarde le score precedent
    if(ps != NULL){ //ps != NULL => on vient de faire une Partiesimple
      save_partie_simple(file_score);
    }
    else{ //ps == NULL => on vient de faire une Partiecomplex
      save_partie_complexe(file_score);
    }
  }
  file_score.close();
}
void Snake::save_partie_simple(ofstream& f)const{
  f << "ps" << endl;
  f << *ps << endl;
}
void Snake::save_partie_complexe(ofstream& f)const{
  f << "pc" << endl;
  f << *pc << endl;
}


//On va recreer la partie precedente a partir des donnes sauvegardees dans user.txt
int Snake::set_last_game(ifstream& f){
  string n;
  getline(f,n);
  if(n == "ps"){ //Partiesimple
    return set_partie_simple(f);
  }
  return set_partie_complexe(f); //Partiecomplex
}
int Snake::set_partie_simple(ifstream& f){
  vector<Chemin> c = set_chemin(f);
  vector<Body> b = set_snake(f);
  EatablePastille e = set_eatablepastille(f);
  SmokedPastille s = set_smokedpastille(f);
  VortexPastille v = set_vortexpastille(f);
  ps = new Partiesimple(c,b,e,s,v,previous_score);
  return ps->jeu();
}
int Snake::set_partie_complexe(ifstream& f){
  vector<Chemin> c = set_chemin(f);
  vector<Body> b = set_snake(f);
  EatablePastille e = set_eatablepastille(f);
  SmokedPastille s = set_smokedpastille(f);
  VortexPastille v = set_vortexpastille(f);
  vector<Mur> m = set_mur(f);
  vector<SmokedMur> sm = set_smokedmur(f);
  vector<VortexMur> vm = set_vortexmur(f);
  pc = new Partiecomplex(c,b,m,sm,vm,e,s,v,previous_score);
  cout << pc->print() << endl;
  return pc->jeu();
}
///////////RECUPERE/LE/CONTENU/DU/FICHIER/user.txt/POUR/RECREER/LA/PARTIE/PRECEDENTE////////
//on va parcourir le fichier user.txt entre 2 bornes definies selon la donnee que l'on cherche a extraire,
//on va extraire cette donne et recreer un groupe d'element du jeu : snake, chemins, murs, pastilles...
vector<Chemin> Snake::set_chemin(ifstream& f)const{
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
vector<Body> Snake::set_snake(ifstream& f)const{
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
EatablePastille Snake::set_eatablepastille(ifstream& f)const{
  EatablePastille e;
  string n;
  /*do{
    getline(f, n);
    cout << n << endl;
  }while(n!= "eatable");*/
  getline(f, n);
  return EatablePastille(positionX(n), positionY(n));
}
SmokedPastille Snake::set_smokedpastille(ifstream& f)const{
  SmokedPastille s;
  string n;
  do{
    getline(f, n);
  }while(n!= "smokedp");
  getline(f, n);
  return SmokedPastille(positionX(n), positionY(n));
}
VortexPastille Snake::set_vortexpastille(ifstream& f)const{
  VortexPastille v;
  string n;
  do{
    getline(f, n);
  }while(n != "vortexp");
  getline(f, n);
  return VortexPastille(positionX(n), positionY(n));
}
vector<Mur> Snake::set_mur(ifstream& f)const{
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
vector<SmokedMur> Snake::set_smokedmur(ifstream& f)const{
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
vector<VortexMur> Snake::set_vortexmur(ifstream& f)const{
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

int Snake::positionX(const string& s)const{
  string delim(" ");
  string x = s.substr(0, s.find(delim));
  return (stoi(x));
}
int Snake::positionY(const string& s)const{
  string delim(" ");
  string y = s.substr(s.find(delim) + 1, s.size() - 1);
  return (stoi(y));
}
////////////////////////////////////////////////////////////////////////////////////////////



