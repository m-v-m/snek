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


struct snake {
	//snake *next;
	snake *prev;
	int x, y;
	int direction; //1=left 2=up 3=down 4=right
	
}*snakeHead, *snakeTail;

struct food {
	int x;
	int y;
	sf::Sprite foodSprite;
}food;

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

bool isSnakeOccupying() {
	snake *p = snakeHead;
		if (p->x == food.x && p->y == food.y)
			return true;
	return false;
}

void initialize() {
	snakeHead->x = rand() % 20 + 2;
	snakeHead->y = rand() % 12 + 2;
	snakeHead->prev = NULL;
	snakeTail = snakeHead;
	if (24 - snakeHead->x <= 17)
		snakeHead->direction = 1;
	else snakeHead->direction = 4;
}

void spawnFood() {
	food.x = rand() % 23 + 1;
	food.y = rand() % 13 + 2;
}

void growSnake() {

}

int main()
{	
	snakeHead = new snake;
	srand(time(NULL));
	initialize();
	spawnFood();
	sf::Time difficulty = sf::milliseconds(250);
	sf::Texture snakeTexture;
	sf::Texture foodTexture;
	sf::Sprite snakeSprite;
	sf::Time elapsed;
	sf::Clock clock;
	bool hasPressed = false;

	if (!snakeTexture.loadFromFile("head.png")) {}
	snakeSprite.setTexture(snakeTexture);
	snakeSprite.setPosition(snakeHead->x*32, snakeHead->y*32);
	if (!foodTexture.loadFromFile("food.png")) {}
	food.foodSprite.setTexture(foodTexture);
	food.foodSprite.setPosition(food.x * 32, food.y * 32);

	while (gameFrame.isOpen()) {
		sf::Event e;
		gameFrame.clear(sf::Color::Black);		
		gameFrame.draw(snakeSprite);
		gameFrame.draw(food.foodSprite);
		drawWall();
		gameFrame.display();
		clock.restart();
		do {
			elapsed = clock.getElapsedTime();
		} while (elapsed <= difficulty);
		while (gameFrame.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				gameFrame.close();
			if (e.type == sf::Event::KeyPressed)
				switch (e.key.code) {
				case sf::Keyboard::Left:
					if (snakeHead->direction != 1 && snakeHead->direction != 4 && !hasPressed) {
						snakeHead->direction = 1;
						hasPressed = true;
					}
					break;
				case sf::Keyboard::Up:
					if (snakeHead->direction != 2 && snakeHead->direction != 3 && !hasPressed) {
						snakeHead->direction = 2;
						hasPressed = true;
					}
					break;
				case sf::Keyboard::Down:
					if (snakeHead->direction != 2 && snakeHead->direction != 3 && !hasPressed) {
						snakeHead->direction = 3;
						hasPressed = true;
					}
					break;
				case sf::Keyboard::Right:
					if (snakeHead->direction != 1 && snakeHead->direction != 4 && !hasPressed) {
						snakeHead->direction = 4;
						hasPressed = true;
					}
					break;
				case sf::Keyboard::S:
					growSnake();
					break;
				}
		}
		hasPressed = false;
		switch (snakeHead->direction) {
		case 1:
			snakeSprite.move(-32, 0);
			snakeHead->x--;
			break;
		case 2:
			snakeSprite.move(0, -32);
			snakeHead->y--;
			break;
		case 3:
			snakeSprite.move(0, 32);
			snakeHead->y++;
			break;
		case 4:
			snakeSprite.move(32, 0);
			snakeHead->x++;
			break;
		}
		system("CLS");
		isSnakeOccupying() ? std::cout << "yes\n" : std::cout << "no\n";
		if (isSnakeOccupying()) {
			spawnFood();
			food.foodSprite.setPosition(food.x * 32, food.y * 32);
		}
		std::cout << "x:" << snakeHead->x << "\ny:" << snakeHead->y;
	}
	return 0;
}
