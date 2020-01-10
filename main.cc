#include "Snake.hh"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(){
	// taille , nom , titre affiché, bouton fermé , pas resizeable , le type renderWindow permet de dessiner dans la fenetre
sf::Window fenetre(sf::VideoMode(1071,1071), "Snake 4.0",sf::Style::Titlebar | sf::Style::Close);

 while (fenetre.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (fenetre.pollEvent(event))	
        {
        	 Snake a;
            // "close requested"
            if (event.type == sf::Event::Closed)
                fenetre.close();
        }

         fenetre.display();
    }



 
  return 0;
}
