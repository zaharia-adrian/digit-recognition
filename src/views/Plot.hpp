#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Plot {

	sf::RectangleShape r;
	sf::Font font;
	sf::Text digit;
	const float width = 40, height = 200, gap = 15;
	std::vector<float> v;

public:
	Plot();
	
	void update(std::vector<float>);
	void drawTo(sf::RenderWindow&);
};