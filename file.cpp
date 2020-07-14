#include<SFML\Graphics.hpp>
#include<time.h>
#include<stdlib.h>
#include<vector>

class Game {

private:
	sf::RenderWindow window;
	sf::RectangleShape moving_bar;
	std::vector<sf::RectangleShape> rectangles;
	sf::Event evnt ;
	int index;

private:
	void pollevent();
	void render();
	void update();

public:
	void run();

	Game() {
		window.create(sf::VideoMode(1000, 1000), "Bubble Sort Visualiser", sf::Style::Close);
		window.setFramerateLimit(5);
		
		for (int i = 0; i < 9; ++i) {
			sf::RectangleShape rectangle;
			int size = rand() % 400;
			int x = rand() % 500;
			rectangle.setSize(sf::Vector2f(50.0f, size));
			rectangle.setPosition(sf::Vector2f( 100*i + 50 , 0));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(sf::Color::Black);
			rectangles.push_back(rectangle);
			std::cout << rectangles[i].getPosition().x <<" "<< rectangles[i].getPosition().y << std::endl;
		}

		moving_bar = rectangles[0];
		index = 0;
	}

};

void Game::run() {
	while (window.isOpen()) {
		pollevent();
		update();
		render();
	}
}

void Game::pollevent() {
	if (window.pollEvent(evnt)) {
		if (evnt.type == evnt.Closed)
			window.close();
	}
}

void Game::update() {
	if (index == rectangles.size() - 1)
		index = 0;
	if (rectangles[index].getSize().y > rectangles[index + 1].getSize().y) {
		sf::Vector2f r = rectangles[index].getSize();sf::Vector2f s = rectangles[index + 1].getSize();
		rectangles[index].setSize(s);
		rectangles[index + 1].setSize(r);
	}
	index++;
}

void Game::render() {
	window.clear(sf::Color::White);

	for (size_t i = 0; i < rectangles.size(); ++i) {
		window.draw(rectangles[i]);
	}

	window.display();
}

int main() {
	srand((unsigned int)time(0));
	Game game;
	game.run();
	return 0;
}
