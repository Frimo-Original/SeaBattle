#include <SFML/Graphics.hpp>

namespace sb
{
	struct Coordinate {
		int x, y;
	};

	sf::VertexArray getLine(float x1, float y1, float x2, float y2, sf::Color color)
	{
		sf::VertexArray line(sf::Lines, 2);

		line[0].position = sf::Vector2f(x1, y1);
		line[1].position = sf::Vector2f(x2, y2);
		line[0].color = line[1].color = color;

		return line;
	}

	class Sprite : public sf::Sprite
	{
	private:
		sf::Texture texture;
	public:
		Sprite(sf::String path, Coordinate coordinate) {
			texture.loadFromFile(path);
			setTexture(texture);
			setPosition(coordinate.x, coordinate.y);
		}
	};

	namespace Buttons
	{
		enum class StatusButton
		{
			BUTTON,
			BUTTON_MOUSE_MOVED,
			BUTTON_PRESS
		};

		class Button
		{
		private:
			Sprite button;
			Sprite buttonMouseMoved;
			Sprite buttonPress;
			Coordinate coordinate;
			StatusButton status;
		public:
			Button(std::string pathButton, std::string pathButtonMouseMoved, std::string pathButtonPress, Coordinate coordinate)
				:button(pathButton, coordinate), buttonMouseMoved(pathButtonMouseMoved, coordinate), buttonPress(pathButtonPress, coordinate) {
				status = StatusButton::BUTTON;
			}

			void setStatus(StatusButton status) {
				this->status = status;
			}

			StatusButton getStatus() {
				return status;
			}

			Sprite getSprite() {
				switch (status)
				{
				case StatusButton::BUTTON:
					return button;

				case StatusButton::BUTTON_MOUSE_MOVED:
					return buttonMouseMoved;

				case StatusButton::BUTTON_PRESS:
					return buttonPress;
				}
			}
		};
	}
}