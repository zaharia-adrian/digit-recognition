#pragma once

#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
	std::function<void()> onClick;
	sf::RectangleShape box;
	sf::Text txt;
	sf::Font font;

	bool isMouseOver(sf::RenderWindow&);
public:
	Button(std::string, sf::Vector2f, std::function<void()> = [&]() {});
	void handleEvent(sf::RenderWindow&, sf::Event);
	void drawTo(sf::RenderWindow&);
};
