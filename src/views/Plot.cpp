
#include "Plot.hpp"


Plot::Plot() {
	if (!font.loadFromFile("../../../assets/fonts/Roboto-Regular.ttf")) {
		std::cout << "Could not load the font!";
	}
	digit.setFont(font);
	digit.setFillColor(sf::Color::White);
	digit.setCharacterSize(21);
	v = std::vector<float>(10,0.0f);
}

void Plot::drawTo(sf::RenderWindow& window) {
	float widthOffset = 1000, heightOffset = 520;

	

	r.setFillColor(sf::Color(56,66,76));
	r.setSize({ width, height });
	float widthDigitPos = widthOffset + (width - digit.getLocalBounds().width) / 2 - (digit.getLocalBounds().left);
	for (int i = 0;i <= 9;i++) {
		digit.setString(std::to_string(i));
		digit.setPosition({widthDigitPos + i * (width + gap), heightOffset + height + 5});
		window.draw(digit);
		r.setPosition({ widthOffset + i * (width + gap), heightOffset});
		window.draw(r);
	}
	r.setFillColor(sf::Color(126,136,146));

	for (int i = 0;i <= 9;i++) {
		float _height = v[i] * height;
		r.setSize({ width, _height });
		r.setPosition({ widthOffset + i * (width + gap), heightOffset + height - _height });
		window.draw(r);
	}
}
void Plot::update(std::vector<float> _v) {
	v = _v;
}