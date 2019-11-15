#include <SFML/Graphics.hpp>

using namespace sf;

VertexArray getLine(float x1, float y1, float x2, float y2, Color color)
{
	VertexArray line(Lines, 2);

	line[0].position = Vector2f(x1, y1);
	line[1].position = Vector2f(x2, y2);
	line[0].color = line[1].color = color;

	return line;
}