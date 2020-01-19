#include "Snake.hh"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


//-------------------------------------------------------------------------------------------------------------------------------
//Dessin WINDOW ET CONTOURS

 // WINDOW initialisation , pas de fonction sinon bug

sf::RenderWindow window(sf::VideoMode(WINDOW,WINDOW), "Snake 4.0",sf::Style::Titlebar | sf::Style::Close);
int i = DrawFond(window);
if (!i){
    return EXIT_FAILURE;
}

   

    //CONTOUR
  


 
               // penser a faire window.close(); à la fin du jeu
        
       
//--------------------------------------------------------------------------------------------------------------------------------

//FONCTION DRAW
        // getElementMatrixptr(int i, int j)const{ return matrixGame[i][j];}
        // MatrixGame
        // GAME_SIZE = 15;

        int DrawFond(sf::Window fenetre){

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

            fenetre.draw(spriteFond);
            fenetre.draw(spriteContour1);
            fenetre.draw(spriteContour2);
            fenetre.draw(spriteContour3);
            fenetre.draw(spriteContour4);
    }

//-------------------------------------------------------------------------------------------------------------
        void draw_Game(sf::Window fenetre){
             fenetre.clear();
             int v = drawFond(fenetre);
             Element*  ElementMatrice;
            for (int i = 0; i < 16; ++i)
            {
                for (int j = 0; j < 16; ++j)
                {
                    ElementMatrice = getElementMatrixptr(int i, int j);
                    fenetre.draw(ElementMatrice->sprite);


                }
            }
            fenetre.display();
        }

int main(){


}

