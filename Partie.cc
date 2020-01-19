#include "Partie.hh"




int Partie::DrawFond(){
  cout<<"draw_fond"<<endl; 

    sf::Texture textureFond;
    if (!textureFond.loadFromFile("images/Chemin.png", sf::IntRect(0,0,WINDOW,WINDOW))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteFond(textureFond);

  sf::Texture contour1; 
  if (!contour1.loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0,0,WINDOW,TAILLEIMAGE))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour1(contour1);

  sf::Texture contour2; 
  if (!contour2.loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0,0,TAILLEIMAGE,WINDOW))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour2(contour2);


  sf::Texture contour3; 
  if (!contour3.loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0,0,WINDOW,TAILLEIMAGE))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour3(contour3);
  spriteContour3.setPosition(sf::Vector2f(0, 650.f)); // absolute position

  sf::Texture contour4; 
  if (!contour4.loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(0,0,TAILLEIMAGE,WINDOW))){
      return EXIT_FAILURE;
  }
  sf::Sprite spriteContour4(contour4);
  spriteContour4.setPosition(sf::Vector2f(1008.f, 0)); // absolute position

  (this->window).draw(spriteFond);
  (this->window).draw(spriteContour1);
  (this->window).draw(spriteContour2);
  (this->window).draw(spriteContour3);
  (this->window).draw(spriteContour4);

  return 1; 
}

//-------------------------------------------------------------------------------------------------------------
void Partie::draw_Game(Element ***matrice){
     int v = 0; 
     v = DrawFond();
     if(!v){cout<<"Erreur DrawFond"<<endl; }
     
     Element*  ElementMatrice;

    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {   
            ElementMatrice = matrice[i][j]; 
            (this->window).draw(ElementMatrice->getSprite());


        }
    }
}



const int& Partie::getNbPoints()const{ return this->nbPoints;}
const vector<Chemin>& Partie::getChemin()const{ return this->chemin;}
const vector<Body>& Partie::getSnake()const{ return this->snake;}
const EatablePastille& Partie::getEatablePastille()const{ return this->pastilleEatable;}
const SmokedPastille& Partie::getSmokedPastille()const{ return this->pastilleSmoked;}
const VortexPastille& Partie::getVortexPastille()const{ return this->pastilleVortex;}
 Element*** Partie::getMatrix(){ return this->matrixGame; }
Element* Partie::getElementMatrixptr(int i, int j){ return matrixGame[i][j];}
//const Element Partie::getElementMatrix(int i, int j)const{ return *(matrixGame[i][j]);}
int Partie::find_rand_chemin()const{
  return rand() % ((int)this->chemin.size() - 1);
}
//////////////////////////////////////////////////////////////////////////////////
void Partie::printSnake(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const{
  vector<Body>::const_iterator it;
  for(it = snake.begin(); it != snake.end(); it++){
    if(it == snake.begin()){
      Tete t = static_cast<Tete>(snake.front());
      tabPrint[t.getX() + 1][t.getY() + 1] = t.print();
    }
    else{
      tabPrint[it->getX() + 1][it->getY() + 1] = it->print();
    }
  }
}
void Partie::print_bord(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const{
  //horizontal
  for(int i = 0; i < GAME_SIZE_PRINT; i++){
    tabPrint[0][i] = "#";
    tabPrint[GAME_SIZE_PRINT - 1][i] = "#";
  }
  //vertical
  for(int i = 0; i < GAME_SIZE_PRINT - 1; i++){
    tabPrint[i + 1][0] = "#";
    tabPrint[i + 1][GAME_SIZE_PRINT - 1] = "#";
  }
}
string Partie::printTab(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const{
  stringstream s;
  //pour n'importe quel type de partie
  print_bord(tabPrint); //on place les murs du bord
  printVector(tabPrint, chemin); //on place les chemins
  printSnake(tabPrint); //on place le snake
  tabPrint[pastilleEatable.getX() + 1][pastilleEatable.getY() + 1] = pastilleEatable.print();
  tabPrint[pastilleSmoked.getX() + 1][pastilleSmoked.getY() + 1] = pastilleSmoked.print();
  tabPrint[pastilleVortex.getX() + 1][pastilleVortex.getY() + 1] = pastilleVortex.print();
  for(int i = 0; i < GAME_SIZE_PRINT; i++){
    for(int j = 0; j < GAME_SIZE_PRINT; j++){
      s << tabPrint[i][j];
    }
    s << "\n";
  }
  s << "\nNombre de points : " << this->nbPoints << endl;
  return s.str();
}
void Partie::to_stringSnake(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const{
  vector<Body>::const_iterator it;
  for(it = snake.begin(); it != snake.end(); it++){
    if(it == snake.begin()){
      Tete t = static_cast<Tete>(snake.front());
      tabPrint[t.getX() + 1][t.getY() + 1] = t.to_string();
    }
    else{
      tabPrint[it->getX() + 1][it->getY() + 1] = it->to_string();
    }
  }
}
string Partie::to_stringTab(string tabPrint[GAME_SIZE_PRINT][GAME_SIZE_PRINT])const{
  string s;
  //pour n'importe quel type de partie
  print_bord(tabPrint); //on place les murs du bord
  to_stringVector(tabPrint, chemin); //on place les chemins
  to_stringSnake(tabPrint); //on place le snake
  for(int i = 0; i < GAME_SIZE_PRINT; i++){
    for(int j = 0; j < GAME_SIZE_PRINT; j++){
      s += tabPrint[i][j];
      //s += "\t";
    }
    s += "\n";
  }
  return s;
}
//////////////////////////////////////////////////////////////////////////////////
int Partie::jeu(){
  
  int machin = DrawFond(); 
  if(!machin){cout<<machin<<" dommage"<<endl; }
  (this->window).display(); 

  char input;
  int positionTeteX, positionTeteY;
  //on cree les thread sur les parties
  /*thread pastilleSmoked_time_management();
  pastilleSmoked_time_management.join()*/
  cout << "Commandes :\n\tz : haut\n\tw : bas\n\tq : gauche\n\td : droite\n\n\techap : quitte le jeu" << endl;
  cin >> input;
  while(input != 27 && game && window.isOpen()){
    //on recupere la position de la tete du snake
    positionTeteX = snake.front().getX();
    positionTeteY = snake.front().getY();
    switch(input){
      case 'z':
        positionTeteX--;
        break;
      case 'w':
        positionTeteX++;
        break;
      case 'd' :
        positionTeteY++;
        break;
      case 'q' :
        positionTeteY--;
        break;
      default :
        //on ne fait rien
        break;
    }

    action(positionTeteX, positionTeteY);
    cout<<"appel draw"<<endl; 

    (this->window).clear();
    draw_Game(this->getMatrix()); 

    (this->window).display();
    cout<<" sortie draw_game"<<endl;
    /*sf::Event event;
    while (window.pollEvent(event))
    {           
      if (event.type == sf::Event::Closed)
      window.close();
    }*/

    cin >> input;
  }
  return this->nbPoints;
}
Element* Partie::is_movement_possible(int positionX, int positionY){
  if(is_bord(positionX, positionY))
    return is_bord_traversable(positionX, positionY);
  if(is_snake_part(positionX, positionY))
    return lose();
  if((matrixGame[positionX][positionY])->is_traversable())
  //A MODIFIER/////////////////////////////////////////////////////////////////////////////////////////
    return matrixGame[positionX][positionY]; //si traversable on peut se deplacer
  return NULL; //si on element pas traversable, on ne peut pas se deplacer
}
bool Partie::is_bord(int positionX, int positionY){
  if(positionX == -1 || positionX == GAME_SIZE || positionY == -1 || positionY == GAME_SIZE)
    return true;
  return false;
}
Element* Partie::deplacer_snake(int positionX, int positionY){
  //pour toute modification de position d'un element, on doit
  //mettre a jour matrixGame
  //mettre a jour l'element
  int positionX_suiv = positionX;
  int positionY_suiv = positionY;
  int positionX_prec, positionY_prec;
  Element* element_suiv = matrixGame[positionX][positionY];
  vector<Body>::iterator it;
  for(it = snake.begin(); it != snake.end(); it++){
    positionX_prec = it->getX();
    positionY_prec = it->getY();
    it->setPosition(positionX_suiv, positionY_suiv); //on met a jour le snake
    matrixGame[positionX_suiv][positionY_suiv] = &(*it); //on met a jour matrixGame
    positionX_suiv = positionX_prec;
    positionY_suiv = positionY_prec;
  }
  element_suiv->setPosition(positionX_suiv, positionY_suiv);
  matrixGame[positionX_suiv][positionY_suiv] = element_suiv;
  return element_suiv;//on retourne le chemin que l'on a modifie
}
Element* Partie::deplacer_snake(Element* e){
  return deplacer_snake(e->getX(), e->getY());
}
bool Partie::pastilleEatable_management(int positionX, int positionY){
  if(positionX == pastilleEatable.getX() && positionY == pastilleEatable.getY()){
    add_body_to_snake(positionX, positionY);
    set_new_Pastille(pastilleEatable); //on met a jour la position de la pastille sur une nouvelle position
    return true; //le snake est sur la pastilleEatable
  }
  return false; //le snake n'est pas sur la pastilleEatable
}
void Partie::add_body_to_snake(int positionX, int positionY){
  //on deplace le snake sur sa nouvelle position
  //on ajoute au snake un body a la position de l'element retourne par deplacer_snake
  snake.push_back(Body(deplacer_snake(positionX, positionY)));
  //on met a jour matrixGame
  placeElement(snake);
  //on supprime l'element retourne par deplacer_snake
  erase_chemin(snake.back().getX(), snake.back().getY());
  this->nbPoints ++; //on augmente le nombre de points a chaque fois que le snake grandit
}
void Partie::erase_chemin(int positionX, int positionY){
  vector<Chemin>::const_iterator it;
  for(it = chemin.begin(); it != chemin.end(); it++){
    if((it->getX() == positionX) && (it->getY() == positionY)){
      chemin.erase(it);
    }
  }
  //on met a jour matrixGame
  placeElement(chemin);
}
bool Partie::is_snake_part(int positionX, int positionY){
  //ici on teste si la nouvelle position de la tete du snake sera la position d'une des parties de son corps
  vector<Body>::iterator it;
  //it = (snake.begin() + 3) car avec la configuration du jeu, la tete du snake ne pourra jamais
  //se deplacer sur snake.begin() = la  tete elle meme, ni sur les 2 premieres parties de son corps
  //      Body2
  // tete Body1  comme nous pouvons le voir ici (le pire cas), au prochain mouvement de tete, tete ne pourra
  //      Body2  pas se deplacer sur Body1 ni un des 2 Body2
  if(snake.size() > 3){
    for(it = (snake.begin() + 3); it != snake.end(); it++){
      if((it->getX() == positionX) && (it->getY() == positionY))
        return true;
    }
  }
  return false;
}
Element* Partie::lose(){
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  cout << "Vous vous êtes mordu la queue !" << endl;
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  game = false; //on indique que le jeu est fini
  return NULL;
}
