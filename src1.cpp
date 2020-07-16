#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<iostream>

class Game {

private:
	sf::RenderWindow window;
	sf::RectangleShape moving_bar;
	std::vector<sf::RectangleShape> rectangles;
	sf::Event evnt ;
	int index;
	sf::RectangleShape button_generate , button_sort;
	sf::Vector2i mouse_press; 
	bool flag1=false , flag2=false;

private:
	void pollevent();
	void render();
	void update();

public:
	void run();

	Game() {
		window.create(sf::VideoMode(1000, 1000), "Bubble Sort Visualiser", sf::Style::Close);
		window.setFramerateLimit(5);
		sf::Color color1(11, 105, 35);

		for (int i = 0; i < 16; ++i) {
			sf::RectangleShape rectangle;
			int size = rand() % 400;
			int x = rand() % 500;
			rectangle.setSize(sf::Vector2f(50.0f, size));
			rectangle.setPosition(sf::Vector2f(100 + 50 * i, 0));
			rectangle.setFillColor(color1);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(sf::Color::Black);
			rectangles.push_back(rectangle);
		}

		mouse_press.x = 0;mouse_press.y = 0;
		moving_bar = rectangles[0];
		index = 0;

		button_generate.setSize(sf::Vector2f( 80 , 30 ));
		button_generate.setPosition(10 , 800);
		button_generate.setFillColor(color1);
		button_generate.setOutlineThickness(1);
		button_generate.setOutlineColor(sf::Color::Black);
		button_sort.setSize(sf::Vector2f(80, 30));
		button_sort.setPosition(10, 840);
		button_sort.setFillColor(color1);
		button_sort.setOutlineThickness(1);
		button_sort.setOutlineColor(sf::Color::Black);
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
		else if (evnt.type == evnt.MouseButtonPressed)
			mouse_press = sf::Mouse::getPosition(window);
	}
}

void Game::update() {
	//std::cout << mouse_press.x << " " << mouse_press.y << std::endl;
	if ((mouse_press.x >= 10 && mouse_press.x <= 90) && (mouse_press.y >= 840 && mouse_press.y <= 870))
		flag2 = true;
	else if ((mouse_press.x >= 10 && mouse_press.x <= 90) && (mouse_press.y >= 800 && mouse_press.y <= 830) && !flag2)
		flag1 = true;
	if (flag2) {
		if (index == rectangles.size() - 1)
			index = 0;
		if (rectangles[index].getSize().y > rectangles[index + 1].getSize().y) {
			sf::Vector2f r = rectangles[index].getSize();sf::Vector2f s = rectangles[index + 1].getSize();
			rectangles[index].setSize(s);
			rectangles[index + 1].setSize(r);
		}
		index++;
	}
	if (flag1) {
		sf::Color color1(11, 105, 35);
		rectangles.clear();
		for (int i = 0; i < 16; ++i) {
			sf::RectangleShape rectangle;
			int size = rand() % 400;
			int x = rand() % 500;
			rectangle.setSize(sf::Vector2f(50.0f, size));
			rectangle.setPosition(sf::Vector2f(100 + 50 * i, 0));
			rectangle.setFillColor(color1);
			rectangle.setOutlineThickness(1);
			rectangle.setOutlineColor(sf::Color::Black);
			rectangles.push_back(rectangle);
		}
		flag1 = false;
	}
	mouse_press.x = 0;mouse_press.y = 0;
}

void Game::render() {
	sf::Color color(173, 216, 230) , color1(11, 50, 35) , color2(11, 105, 35);
	window.clear(color);

	for (size_t i = 0; i < rectangles.size(); ++i) {
		window.draw(rectangles[i]);
	}
	window.draw(button_generate);
	window.draw(button_sort);
	window.display();
}

int main() {
	srand((unsigned int)time(0));
	Game game;
	game.run();
	return 0;
}
