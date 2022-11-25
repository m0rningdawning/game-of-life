#include <iostream>
#include <cstdlib>
#include <string>
#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 600
#define FRAMES 30

// grid size 38 x 20 20px

int main(void){

	// Window

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life", sf::Style::Close);
	window.setFramerateLimit(FRAMES);
	sf::RectangleShape playArea(sf::Vector2f(760.f, 400.f));
    playArea.setFillColor(sf::Color(255, 255, 255));
	playArea.setPosition(20.f, 20.f);
	playArea.setOutlineThickness(1.f);
	playArea.setOutlineColor(sf::Color(0, 0, 0));

	// Text

	sf::Font font;
	if (!font.loadFromFile("fonts/Roboto/Roboto-Black.ttf")){
		perror("Font");	
	}
	sf::Text title;

	title.setFont(font); // font is a sf::Font
	title.setString("Conway's Game of Life");
	title.setCharacterSize(52); // in pixels, not points!
	title.setFillColor(sf::Color::White);
	title.setOutlineThickness(1.f);
	title.setStyle(sf::Text::Bold);
	title.setPosition(120.f, 420.f);

	// Icons
	
	sf::Texture icon_play;
	if (!icon_play.loadFromFile("textures/icons/icons_1/Button_Play.png"))
		perror("icon_play");
	icon_play.setSmooth(true);
	sf::Sprite button_play;
	button_play.setTexture(icon_play);
	button_play.setScale(sf::Vector2f(0.5f, 0.5f));
	button_play.setPosition(sf::Vector2f(350.f, 500.f));

	sf::Texture icon_reset;
	if (!icon_reset.loadFromFile("textures/icons/icons_1/_Retry.png"))
		perror("icon_reset");
	icon_reset.setSmooth(true);
	sf::Sprite button_reset;
	button_reset.setTexture(icon_reset);
	button_reset.setScale(sf::Vector2f(0.35f, 0.35f));
	button_reset.setPosition(sf::Vector2f(440.f, 513.f));

	sf::Texture icon_pause;
	if (!icon_pause.loadFromFile("textures/icons/icons_1/_Pause.png"))
		perror("icon_play");

	// Cells
	
	sf::RectangleShape cell(sf::Vector2f(20.f, 20.f));
	// Main loop

	bool playingStatus = false;

    while (window.isOpen()){
        sf::Event event;

		// Event polling

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
        }

		// Render

		window.clear(sf::Color(128, 128, 128));
		window.draw(playArea);
		for (int x = 0; x < 38; x++){
			for (int y = 0; y < 20; y++){
				cell.setPosition(x * 20 + 20, y * 20 + 20);
				cell.setOutlineThickness(1.f);
				cell.setOutlineColor(sf::Color::Black);
				window.draw(cell);
			}
		}
		window.draw(title);
		window.draw(button_play);
		window.draw(button_reset);
        window.display();
    }
    return 0;
}
