#include "digit-recognition.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int gridSize = 28; ///standard for MNIST dataset

int main()
{
	NN nn({ gridSize * gridSize,500, 10 });
	
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Digit recognition");
	window.setFramerateLimit(60);

	Plot plot;
	Grid grid(gridSize, gridSize); 

	Button resetBtn("Reset", { 1000,120 }, [&]() {
		grid.reset();
	});
	Button queryBtn("Query", { 1000, 200 }, [&]() {
		plot.update(nn.query(grid.getV()));
	});
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			}
			grid.handleEvent(window, event);

			resetBtn.handleEvent(window, event);
			queryBtn.handleEvent(window, event);

		}
		window.clear(sf::Color(36,46,56));
		

		grid.drawTo(window);

		resetBtn.drawTo(window);
		queryBtn.drawTo(window);

		plot.drawTo(window);

		window.display();
	}

	return 0;
}

