#include <iostream>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

// Settings

int FRAMES = 15;
#define WIDTH 800
#define HEIGHT 600
#define HORIZONTAL 38
#define VERTICAL 20
#define SIZE 20

bool isAlive(int arr[VERTICAL][HORIZONTAL], int y, int x){

	int amount = 0;

	// Check neighbours
	
	if(y > 0 && arr[y-1][x] == 1) 
		amount += 1;
	if(x > 0 && y > 0 && arr[y-1][x-1] == 1) 
		amount += 1;
	if(x > 0 && arr[y][x-1] == 1) 
		amount += 1;
	if(x > 0 && y < VERTICAL - 1 && arr[y+1][x-1] == 1) 
		amount += 1;
	if(y < VERTICAL - 1 && arr[y+1][x] == 1) 
		amount += 1;
	if(x < HORIZONTAL - 1 && y < VERTICAL - 1 && arr[y+1][x+1] == 1) 
		amount += 1;
	if(x < HORIZONTAL - 1 && arr[y][x+1] == 1) 
		amount += 1;
	if(x < HORIZONTAL - 1 && y > 0 && arr[y-1][x+1] == 1) 
		amount += 1;

	// Decide if a cell is dead or alive
	
	if(arr[y][x] == 1 && amount < 2) 
		return false;
	if(arr[y][x] == 1 && (amount == 2 || amount == 3)) 
		return true;
	if(arr[y][x] == 1 && amount > 3) 
		return false;
	if(arr[y][x] == 0 && amount == 3) 
		return true;

	return false;
}

void randomizeCells(int state[VERTICAL][HORIZONTAL], int stateNext[VERTICAL][HORIZONTAL]){
	for (int y = 0; y < VERTICAL; y++){
		for (int x = 0; x < HORIZONTAL; x++){
			state[y][x] = rand() % 2;
			stateNext[y][x] = 0;
		}
	}
}

int main(void){

	srand(time(NULL));

	// Window

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Conway's Game of Life", sf::Style::Close);
	window.setFramerateLimit(FRAMES);
	sf::RectangleShape playArea(sf::Vector2f(760.f, 400.f));
    playArea.setFillColor(sf::Color::White);
	playArea.setPosition(20.f, 20.f);
	playArea.setOutlineThickness(1.f);
	playArea.setOutlineColor(sf::Color(0, 0, 0));

	// Text

	sf::Font font;
	if (!font.loadFromFile("fonts/Roboto/Roboto-Black.ttf")){
		perror("Font");	
	}
	sf::Text title;

	title.setFont(font);
	title.setString("Conway's Game of Life");
	title.setCharacterSize(52);
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
	button_play.setScale(sf::Vector2f(1.f, 1.f));
	button_play.setPosition(sf::Vector2f(358.f, 500.f));

	sf::Texture icon_reset;
	if (!icon_reset.loadFromFile("textures/icons/icons_1/_Retry.png"))
		perror("icon_reset");
	icon_reset.setSmooth(true);
	sf::Sprite button_reset;
	button_reset.setTexture(icon_reset);
	button_reset.setScale(sf::Vector2f(0.35f, 0.35f));
	button_reset.setPosition(sf::Vector2f(448.f, 513.f));

	sf::Texture icon_pause;
	if (!icon_pause.loadFromFile("textures/icons/icons_1/_Pause.png"))
		perror("icon_pause");
	icon_pause.setSmooth(true);

	sf::Texture icon_randomize;
	if (!icon_randomize.loadFromFile("textures/icons/icons_1/_Randomize.png"))
		perror("icon_randomize");
	icon_randomize.setSmooth(true);
	sf::Sprite button_randomize;
	button_randomize.setTexture(icon_randomize);
	button_randomize.setScale(sf::Vector2f(0.35f, 0.35f));
	button_randomize.setPosition(sf::Vector2f(296.f, 513.f));


	// Cells & arrays
	
	sf::RectangleShape cell(sf::Vector2f(20.f, 20.f));

	int state[VERTICAL][HORIZONTAL];
	int stateNext[VERTICAL][HORIZONTAL];

	randomizeCells(state, stateNext);	

	// Main loop
	
	bool playingStatus = false;

    while (window.isOpen()){

		// Event polling
        
		sf::Event event;

        while (window.pollEvent(event)){
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left){
						int x = (event.mouseButton.x)/SIZE;
						printf("Mous pos x: %d, %f\n", x, event.mouseButton.x);
						int y = (event.mouseButton.y)/SIZE;
						printf("Mous pos y: %d, %f\n", y, event.mouseButton.y);
						if (x >= 0 && x <= HORIZONTAL && y >= 0 && y <= VERTICAL)
							state[y-1][x-1] = !state[y-1][x-1];

						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
						if (button_play.getGlobalBounds().contains(mousePosF)){
							button_play.setTexture(icon_pause);
							playingStatus = !playingStatus;
							if(!playingStatus)
								button_play.setTexture(icon_play);
						}
						if (button_randomize.getGlobalBounds().contains(mousePosF)){
							playingStatus = false;
							randomizeCells(state, stateNext);
							button_play.setTexture(icon_play);
						}
						if (button_reset.getGlobalBounds().contains(mousePosF)){
							playingStatus = false;
							button_play.setTexture(icon_play);
							for (int y = 0; y < VERTICAL; y++){
								for (int x = 0; x < HORIZONTAL; x++){
									state[y][x] = 0;
									stateNext[y][x] = 0;
								}
							}
						}
					}
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					if (event.key.code == sf::Keyboard::Space){
						playingStatus = !playingStatus;
						if (playingStatus){
							button_play.setTexture(icon_pause);
						}
						else {
							button_play.setTexture(icon_play);
						}
					}
					if (event.key.code == sf::Keyboard::R){
						playingStatus = false;
						randomizeCells(state, stateNext);
						button_play.setTexture(icon_play);
					}
					if (event.key.code == sf::Keyboard::C){
						playingStatus = false;
						button_play.setTexture(icon_play);
					    for (int y = 0; y < VERTICAL; y++){
							for (int x = 0; x < HORIZONTAL; x++){
								state[y][x] = 0;
								stateNext[y][x] = 0;
							}
						}
					}
					if (event.key.code == sf::Keyboard::Down){
						if (FRAMES > 5)
							FRAMES -= 5;
						window.setFramerateLimit(FRAMES);
					}
					if (event.key.code == sf::Keyboard::Up){
						if (FRAMES < 30)
							FRAMES += 5;
						window.setFramerateLimit(FRAMES);
					}
					break;
			}
        }

		// Draw on screen

		window.clear(sf::Color(128, 128, 128));
		window.draw(playArea);
		window.draw(title);
		window.draw(button_play);
		window.draw(button_reset);
		window.draw(button_randomize);

		// Draw cell

		for (int y = 0; y < VERTICAL; y++){
			for (int x = 0; x < HORIZONTAL; x++){
				cell.setPosition(x * SIZE + SIZE, y * SIZE + SIZE);
				cell.setOutlineThickness(1.f);
				cell.setOutlineColor(sf::Color::Black);
				if (state[y][x] == 1)
                    cell.setFillColor(sf::Color(128, 128, 128));
                else
                    cell.setFillColor(sf::Color::White);
				window.draw(cell);
		
				//Check if alive

				if(playingStatus){
					if(isAlive(state, y, x))
						stateNext[y][x] = 1;
					else
						stateNext[y][x] = 0;
				}
			}
		}

		// Move stateNext array to state

		if (playingStatus)
			for (int y = 0; y < VERTICAL; y++)
				for (int x = 0; x < HORIZONTAL; x++)
					state[y][x] = stateNext[y][x];
		window.display();
	}
    return 0;
}
