
#include "Plot.hpp"


Plot::Plot() {
	v = std::vector<float>(10,0.0f);
}

void Plot::drawTo(sf::RenderWindow& window) {
	float widthOffset = 1000, heightOffset = 700;

	r.setFillColor(sf::Color::Cyan);
	r.setSize({ width, height });
	for (int i = 0;i <= 9;i++) {
		r.setPosition({ widthOffset + i * (width + gap), heightOffset});
		window.draw(r);
	}
	r.setFillColor(sf::Color::Blue);
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