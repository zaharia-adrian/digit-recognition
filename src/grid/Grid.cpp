#include "Grid.hpp"

Grid::Grid(int _rows, int _columns) :
	rows(_rows),
	columns(_columns),
	isDragging(false),
	flow(1.0f)
{

	v.resize(rows * columns);
	pos.resize(rows * columns);

	auto images = FileManager::loadMNISTImages("../../../assets/mnist/train-images.idx3-ubyte");
	for (int idx = 0; idx < rows * columns; idx++) {
		pos[idx] = sf::Vector2f(posX + idx % columns * (boxSize + gap) - boxSize / 2, posY + idx / columns * (boxSize + gap) - boxSize / 2);
		v[idx] = (static_cast<float>(images[100][idx]) / 255);
	}

}

void Grid::handleEvent(sf::RenderWindow& window, sf::Event event) {
	switch (event.type) {
	case sf::Event::MouseMoved:
		if (isDragging) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (isMouseOver(mousePos)) updateGrid(mousePos);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
			isDragging = false;
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Left) {
			isDragging = true;
		}
		break;
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::R:
			reset();
			break;
		}
		break;
	default:break;
	}
}
bool Grid::isMouseOver(sf::Vector2i mousePos) {

	int width = (boxSize + gap) * columns - gap;
	int height = (boxSize + gap) * rows - gap;

	if (mousePos.x < posX || mousePos.x > posX + width) return 0;
	if (mousePos.y < posY || mousePos.y > posY + height) return 0;
	return 1;
}
void Grid::reset() {
	for (float& val : v) val = 0;	
}
void Grid::updateGrid(sf::Vector2i mousePos) {
	///y = idx / columns, x = idx % columns, idx = y * columns + x

	const float distMax = boxSize + gap;

	int dx[] = { -1, -1, 0, 1, 1,  1,  0, -1, 0};
	int dy[] = {  0,  1, 1, 1, 0, -1, -1, -1, 0};

	int x = (mousePos.x - posX) / (boxSize + gap);
	int y = (mousePos.y - posY) / (boxSize + gap);


	for (int k = 0; k < 9; k++) {

		int newY = y + dy[k];
		int newX = x + dx[k];
		if (newX < 0 || newY < 0 || newX >= columns || newY >= rows) continue;

		int idx = newY * columns + newX;
		float distX = pos[idx].x - mousePos.x;
		float distY = pos[idx].y - mousePos.y;
		float dist = distX * distX + distY * distY;

		if (dist < distMax * distMax) {

			float factor = (1.0f / (1.0f + dist / (distMax * distMax))) * flow;
			v[idx] = std::min(1.0f, v[idx] + factor);
		}
	}
}


void Grid::drawTo(sf::RenderWindow& window) {
	
	sf::RectangleShape box({ boxSize, boxSize });
	
	for (int idx = 0; idx < rows * columns; idx++ ) {

		box.setPosition(pos[idx]);

		int colorValue = static_cast<int>((1 - v[idx]) * 255);
		box.setFillColor(sf::Color(colorValue, colorValue, colorValue));
		window.draw(box);
		
	}
}
