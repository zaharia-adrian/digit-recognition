#include "Button.hpp"

Button::Button(std::string name, sf::Vector2f pos, std::function<void()> _onClick): onClick(_onClick){
	box.setPosition(pos);
	box.setSize({200,50});
	box.setFillColor(sf::Color(56,66,76));

	if (!font.loadFromFile("../../../assets/fonts/Roboto-Regular.ttf")) {
		std::cout << "Could not load the font!";
	}

	txt.setFont(font);
	txt.setString(name);
	txt.setCharacterSize(24);
	txt.setColor(sf::Color::White);
	
	float xPos = pos.x + (box.getLocalBounds().width - txt.getLocalBounds().width) / 2 - (txt.getLocalBounds().left);
	float yPos = pos.y + (box.getLocalBounds().height - txt.getLocalBounds().height) / 2 - (txt.getLocalBounds().top);

	txt.setPosition({ xPos, yPos });
}
void Button::handleEvent(sf::RenderWindow& window, sf::Event event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Button::Left)
			if (isMouseOver(window)) {
				onClick();
			}
		break;
	default: break;
	}
}


bool Button::isMouseOver(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f btnPos = box.getPosition();

	if (btnPos.x > mousePos.x || btnPos.y > mousePos.y) return false;
	if (btnPos.x + 200 < mousePos.x || btnPos.y + 50 < mousePos.y) return false;

	return true;
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(txt);
}