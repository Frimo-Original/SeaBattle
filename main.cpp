#include <SFML/Graphics.hpp>
#include "DrawElements.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(900, 600), "See battle");

	Texture fonTexture;
	fonTexture.loadFromFile("pictures/water.png");
	Sprite fon;
	fon.setTexture(fonTexture);
	fon.setPosition(0, 0);

	while(window.isOpen())
	{
		Event event;

		while(window.pollEvent(event)) {
			if(event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::Black);

		//draw content

		window.draw(fon);

		for (int i = 0; i <= 10; i++) {
			window.draw(getLine(100 + i * 30, 100, 100 + i * 30, 400, Color::Black));
			window.draw(getLine(100, 100 + i * 30, 400, 100 + i * 30, Color::Black));

			window.draw(getLine(500 + i * 30, 100, 500 + i * 30, 400, Color::Black));
			window.draw(getLine(500, 100 + i * 30, 800, 100 + i * 30, Color::Black));
		}

		window.display();
	}

	return 0;
}