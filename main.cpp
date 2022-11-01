#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

// Visuals

int main(void){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Conway's Game of Life", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::RectangleShape shape(sf::Vector2f(760.f, 400.f));
    shape.setFillColor(sf::Color(255, 255, 255));
	shape.setPosition(20.f, 20.f);
	//shape.setScale(6.3f, 8.6f);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(sf::Color(0, 0, 0));
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear(sf::Color(128, 128, 128));
        window.draw(shape);
        window.display();
    }
    return 0;
}
