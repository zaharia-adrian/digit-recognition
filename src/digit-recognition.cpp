#include "digit-recognition.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int gridSize = 28; ///standard for MNIST dataset

int main()
{
	NN n({28*28,500,10});

	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Digit recognition");
	window.setFramerateLimit(60);

	
	Plot p;
	Grid grid(gridSize, gridSize); 

	Button reset("Reset", { 1000,70 }, [&]() {
		grid.reset();
	});
	Button query("Query", { 1000, 150 }, [&]() {
		p.update(n.query(grid.getV()));
	});
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
			grid.handleEvent(window, event);

			reset.handleEvent(window, event);
			query.handleEvent(window, event);

		}
		window.clear(sf::Color(36,46,56));
		

		grid.drawTo(window);

		reset.drawTo(window);
		query.drawTo(window);

		p.drawTo(window);

		window.display();
	}

	return 0;
}

