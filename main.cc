#include "Snake.hh"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


const int 

void mainFunction(){

    Snake  a;
}

void mursContour(){

      sf::Texture textureMur;

    if(!textureMur.loadFromFile("images/Murs/Mur_Normal.png", sf::IntRect(200, 400, 32, 60))){
        return EXIT_FAILURE;
    }
    sf::Sprite spriteMur(textureMur);

}

int main(){
    //STATIC GRAPHICS

    // taille , nom , titre affiché, bouton fermé , pas resizeable , le type renderWindow permet de dessiner dans la window
sf::RenderWindow window(sf::VideoMode(1071,1071), "Snake 4.0",sf::Style::Titlebar | sf::Style::Close);

// FOND VERT
sf::Texture fondTexture;
    if (!fondTexture.loadFromFile("images/Chemin.jpg"))
        return EXIT_FAILURE;
    sf::Sprite fond(fondTexture);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 // create a thread with func() as entry point
    sf::Thread thread(&mainFunction);
// lance le snake
    thread.launch();

   

   





 
  return 0;
}
