#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../../src/managers/FileManager.hpp"

class Grid {
	int columns, rows;
	std::vector<float> v;
	std::vector<sf::Vector2f> pos;

	bool isDragging;
	float flow;

	static const int gap = 3;
	static const int boxSize = 20;
	static const int posX = 200;
	static const int posY = 120;

	bool isMouseOver(sf::Vector2i);

public:
	Grid(int, int);

	void reset();
	std::vector<float> getV();

	void handleEvent(sf::RenderWindow&, sf::Event);
	void updateGrid(sf::Vector2i);
	void drawTo(sf::RenderWindow&);
};