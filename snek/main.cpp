#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main()
{

	sf::RenderWindow gameFrame(sf::VideoMode(512, 512, 32), "Snek", sf::Style::Default);
	sf::Sprite snake;sf::Texture texture;
	if (!texture.loadFromFile("head.png")) {}
	snake.setTexture(texture);
	while (gameFrame.isOpen()) {
		sf::Event e;
		gameFrame.clear(sf::Color::Black);		
		gameFrame.draw(snake);
		gameFrame.display();
		while (gameFrame.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				gameFrame.close();
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::S) {
					snake.move(1, 1);
					std::cout << "s";
				}
				break;
			default:
				break;
			}

		}
	}
	return 1;
}