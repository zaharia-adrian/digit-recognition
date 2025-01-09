#include "digit-recognition.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int gridSize = 28; ///standard for MNIST dataset

int main()
{
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Digit recognition");
	window.setFramerateLimit(60);

	Grid grid(gridSize, gridSize); 
	Button btn("Reset", { 1000,70 }, [&]() {
		grid.reset();
	});

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
			grid.handleEvent(window, event);
			btn.handleEvent(window, event);
		}
		window.clear(sf::Color(36,46,56));
		
		grid.drawTo(window);
		btn.drawTo(window);
		window.display();
	}


	return 0;
}

