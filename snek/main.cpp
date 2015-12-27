#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <time.h>
sf::RenderWindow gameFrame(sf::VideoMode(800, 512, 32), "Snek", sf::Style::Default);

int layout[16][25] = {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
						1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int visited[16][25];

//struct player {
//	int direction;
//	int x = 0;
//	int y = 0;
//	sf::Time difficulty = sf::milliseconds(300);
//}player;

struct snake {
	snake *next;
	snake *prev;
	int x, y;
	int direction; //1=left 2=up 3=down 4=right
	
}*snakeHead, *snakeTail;

struct food {
	int x;
	int y;
}
food;

void drawWall() {
	for (int i = 0; i < 16; i++)
			for (int j = 0; j < 25; j++)
				if (layout[i][j]) {
					sf::RectangleShape wall(sf::Vector2f(32, 32));
					wall.setPosition(j * 32, i * 32);
					wall.setFillColor(sf::Color(250, 250, 250));
					gameFrame.draw(wall);
				}
}

bool didSnakePass() {
	snake *p = snakeHead;
	while (p->prev-) {
		if (p->x == food.x && p->y == food.y)
			return true;
	}
	return false;
}

void initialize() {
	//player.x = rand() % 13 + 1;
	//player.y = rand() % 20 + 1;
	//snakeHead->x = player.x;
	//snakeHead->y = player.y;
	snakeHead->x = rand() % 20 + 2;
	snakeHead->y = rand() % 12 + 2;
	snakeHead->next = NULL;
	snakeHead->prev = NULL;
	snakeTail = snakeHead;
	if (24 - snakeHead->x <= 17)
		snakeHead->direction = 1;
	else snakeHead->direction = 4;
	food.x = rand() % 23 + 1;
	food.y = rand() % 14 + 2;
}

int main()
{	
	snakeHead = new snake;
	srand(time(NULL));
	initialize();
	sf::Time difficulty = sf::milliseconds(300);
	sf::Texture texture;
	sf::Sprite snakeSprite;
	sf::Time elapsed;
	sf::Clock clock;
	
	if (!texture.loadFromFile("head.png")) {}
	snakeSprite.setTexture(texture);
	snakeSprite.setPosition(snakeHead->x*32, snakeHead->y*32);
	
	while (gameFrame.isOpen()) {
		sf::Event e;
		gameFrame.clear(sf::Color::Black);		
		gameFrame.draw(snakeSprite);
		drawWall();
		gameFrame.display();
		while (gameFrame.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				gameFrame.close();
		}
		clock.restart();
		do {
			elapsed = clock.getElapsedTime();
		} while (elapsed <= difficulty);
		switch (snakeHead->direction) {
		case 1:
			snakeSprite.move(-10, 0);
			break;
		case 2:
			snakeSprite.move(0, -10);
			break;
		case 3:
			snakeSprite.move(0, 10);
			break;
		case 4:
			snakeSprite.move(10, 0);
			break;
		}
	}
	return 0;
}
