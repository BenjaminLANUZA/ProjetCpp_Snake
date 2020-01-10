#include "Snake.hh"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(){
	// taille , nom , titre affiché, bouton fermé , pas resizeable , le type renderWindow permet de dessiner dans la window
sf::RenderWindow window(sf::VideoMode(1071,1071), "Snake 4.0",sf::Style::Titlebar | sf::Style::Close);

// FOND VERT
sf::Texture fondTexture;
    if (!fondTexture.loadFromFile(images/"chemin.png"))
        return EXIT_FAILURE;
    sf::Sprite fond(fondTexture);

// test mur
    sf::Texture textureMur;
    if(!textureMur.loadFromFile("mur.jpg", sf::IntRect(200, 400, 32, 60))){
        return EXIT_FAILURE;
    }
    sf::Sprite spriteMur(textureMur);

 while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))	
        {
        	 Snake a;
            // "close requested"
            if (event.type == sf::Event::Closed)
                window.close();
        }

         window.display();
    }



 
  return 0;
}
