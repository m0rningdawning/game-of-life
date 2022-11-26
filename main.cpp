#include <iostream>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>

// Settings

#define WIDTH 800
#define HEIGHT 600
#define FRAMES 15
#define HORIZONTAL 38
#define VERTICAL 20
#define SIZE 20

// grid size 38 x 20 20px

bool isAlive(int arr[VERTICAL][HORIZONTAL], int x, int y){

	int amount = 0;

	// Check neighbours
	
	if(x > 0 && arr[x-1][y] == 1) 
		amount += 1;
	if(y > 0 && x > 0 && arr[x-1][y-1] == 1) 
		amount += 1;
	if(y > 0 && arr[x][y-1] == 1) 
		amount += 1;
	if(y > 0 && x < VERTICAL - 1 && arr[x+1][y-1] == 1) 
		amount += 1;
	if(x < VERTICAL - 1 && arr[x+1][y] == 1) 
		amount += 1;
	if(y < HORIZONTAL - 1 && x < VERTICAL - 1 && arr[x+1][y+1] == 1) 
		amount += 1;
	if(y < HORIZONTAL - 1 && arr[x][y+1] == 1) 
		amount += 1;
	if(y < HORIZONTAL - 1 && x > 0 && arr[x-1][y+1] == 1) 
		amount += 1;

	// Decide if a cell is dead or alive
	
	if(arr[x][y] == 1 && amount < 2) 
		return false;
	if(arr[x][y] == 1 && (amount == 2 || amount == 3)) 
		return true;
	if(arr[x][y] == 1 && amount > 3) 
		return false;
	if(arr[x][y] == 0 && amount == 3) 
		return true;

	return false;
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

	// Cells & arrays
	
	sf::RectangleShape cell(sf::Vector2f(20.f, 20.f));

	int state[VERTICAL][HORIZONTAL];
	int stateNext[VERTICAL][HORIZONTAL];

	for (int i = 0; i < VERTICAL; i++){
		for (int j = 0; j < HORIZONTAL; j++){
			state[i][j] = rand() % 2;
			stateNext[i][j] = 0;
		}
	}

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
						int x = (event.mouseButton.y-SIZE)/SIZE;
						int y = (event.mouseButton.x-SIZE)/SIZE;
						if (x >= 0 && x < VERTICAL && y >= 0 && y < HORIZONTAL)
							state[x][y] = !state[x][y];
					}
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					if (event.key.code == sf::Keyboard::Space)
						playingStatus = !playingStatus;
					break;
			}
        }

		// Draw on screen

		window.clear(sf::Color(128, 128, 128));
		window.draw(playArea);
		window.draw(title);
		window.draw(button_play);
		window.draw(button_reset);

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
