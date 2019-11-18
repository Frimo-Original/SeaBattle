#include <SFML/Graphics.hpp>
#include <string>
#include "DrawElements.h"
#include <iostream>

int main()
{
	using namespace sf;

	RenderWindow window(VideoMode(900, 600), "See battle");

	sb::Sprite fon("pictures/fon.jpg", {0, 0});
	sb::Buttons::Button buttonExit{ "pictures/buttons/exit_button/exit.png", "pictures/buttons/exit_button/exit_mouse_moved.png", "pictures/buttons/exit_button/exit_press.png", {530, 450} };
	sb::Buttons::Button buttonNewGame{ "pictures/buttons/new_game_button/new_game.png", "pictures/buttons/new_game_button/new_game_mouse_moved.png", "pictures/buttons/new_game_button/new_game_press.png", {130, 450} };

	Font font;
	font.loadFromFile("fonts/comic.ttf");

	Text textComputer;
	textComputer.setFont(font);
	textComputer.setString("Computer");
	textComputer.setCharacterSize(40);
	textComputer.setFillColor(Color::Blue);
	textComputer.setPosition(150, 20);

	Text textPlayer;
	textPlayer.setFont(font);
	textPlayer.setString("Player");
	textPlayer.setCharacterSize(40);
	textPlayer.setFillColor(Color::Blue);
	textPlayer.setPosition(590, 20);

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

		window.draw(textComputer);
		window.draw(textPlayer);

		window.draw(buttonExit.getSprite());
		window.draw(buttonNewGame.getSprite());

		for(int i = 0; i <= 10; i++) {
			window.draw(sb::getLine(100 + i * 30, 100, 100 + i * 30, 400, Color::Blue));
			window.draw(sb::getLine(100, 100 + i * 30, 400, 100 + i * 30, Color::Blue));

			window.draw(sb::getLine(500 + i * 30, 100, 500 + i * 30, 400, Color::Blue));
			window.draw(sb::getLine(500, 100 + i * 30, 800, 100 + i * 30, Color::Blue));
		}

		window.display();
	}

	return 0;
}