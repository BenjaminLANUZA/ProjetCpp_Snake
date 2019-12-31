#include "Snake.hh"
#include <SFML/Window.hpp>

int main(){
	// taille , nom , titre affiché, bouton fermé , pas resizeable , le type renderWindow permet de dessiner dans la fenetre
sf::RenderWindow window(sf::VideoMode(1071,1071), "Snake 4.0",sf::Style::Titlebar | sf::Style::Close);
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
