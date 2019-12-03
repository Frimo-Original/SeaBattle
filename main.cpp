#include <SFML/Graphics.hpp>
#include <string>
#include "DrawElements.h"
#include <iostream>

#include <ctime>
#include <random>

/*
-1 - space in which the ship cannot be put
0 - empty cell of the playing field
1 - ship
2 - wounded ship
3 - kill ship
4 - was shot
*/

class FieldBattle
{
public:
	static const int WIDTH = 10;
	static const int HEIGHT = 10;

private:
	int** field;
	int amountWounded;

	void zeroingArray() {
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				field[i][j] = 0;
	}

	void setFourShipDeck()
	{
		using namespace sb;

		Coordinate head;
		int routeShip;
		setShipPlacement(routeShip, head, 4);
		arrangeShip(routeShip, head, 4);
	}

	void setThreeShipDeck()
	{
		using namespace sb;

		Coordinate head;
		int routeShip;
		setShipPlacement(routeShip, head, 3);
		arrangeShip(routeShip, head, 3);
		setShipPlacement(routeShip, head, 3);
		arrangeShip(routeShip, head, 3);
	}

	void setTwoShipDeck()
	{
		using namespace sb;

		Coordinate head;
		int routeShip;
		setShipPlacement(routeShip, head, 2);
		arrangeShip(routeShip, head, 2);
		setShipPlacement(routeShip, head, 2);
		arrangeShip(routeShip, head, 2);
		setShipPlacement(routeShip, head, 2);
		arrangeShip(routeShip, head, 2);
	}

	void setOneShipDeck()
	{
		using namespace sb;

		Coordinate head;

		for(int i = 0; i < 4; i++)
			while (true) {
				head = { randomGenerate(WIDTH), randomGenerate(HEIGHT) };

				if (field[head.y][head.x] == 0) {
					field[head.y][head.x] = 1;
					surroundCell(head.x, head.y);
					break;
				}
			}
	}

	void surroundCell(int x, int y) {
		if (checkCoordinate(x - 1, y - 1) && field[y - 1][x - 1] != 1)
			field[y - 1][x - 1] = -1;

		if (checkCoordinate(x, y - 1) && field[y - 1][x] != 1)
			field[y - 1][x] = -1;

		if (checkCoordinate(x + 1, y - 1) && field[y - 1][x + 1] != 1)
			field[y - 1][x + 1] = -1;

		if (checkCoordinate(x + 1, y) && field[y][x + 1] != 1)
			field[y][x + 1] = -1;

		if (checkCoordinate(x + 1, y + 1) && field[y + 1][x + 1] != 1)
			field[y + 1][x + 1] = -1;

		if (checkCoordinate(x, y + 1) && field[y + 1][x] != 1)
			field[y + 1][x] = -1;

		if (checkCoordinate(x - 1, y + 1) && field[y + 1][x - 1] != 1)
			field[y + 1][x - 1] = -1;

		if (checkCoordinate(x - 1, y) && field[y][x - 1] != 1)
			field[y][x - 1] = -1;
	}

	void replaceEnvironment() {
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				if (field[i][j] == -1)
					field[i][j] = 0;
	}

	void setShipPlacement(int& route, sb::Coordinate& head, int sizeShip) {
		bool flag = true;

		while (flag) {
			head = { randomGenerate(WIDTH), randomGenerate(HEIGHT) };
			route = randomGenerate(4);

			if (field[head.y][head.x] != 0)
				continue;

			for (int i = 0; i < 2; i++)
				switch (route)
				{
				case RoutesShip::TOP:
					if (head.y - (sizeShip - 1) < 0 && i == 0)
						route = RoutesShip::BOTTOM;

					else
						if (field[head.y - (sizeShip - 1)][head.x] == 0)
							flag = false;

					break;

				case RoutesShip::RIGHT:
					if (head.x + (sizeShip - 1) > 9 && i == 0)
						route = RoutesShip::LEFT;

					else
						if (field[head.y][head.x + (sizeShip - 1)] == 0)
							flag = false;

					break;

				case RoutesShip::BOTTOM:
					if (head.y + (sizeShip - 1) > 9 && i == 0)
						route = RoutesShip::TOP;

					else
						if (field[head.y + (sizeShip - 1)][head.x] == 0)
							flag = false;

					break;

				case RoutesShip::LEFT:
					if (head.x - (sizeShip - 1) < 0 && i == 0)
						route = RoutesShip::RIGHT;

					else
						if (field[head.y][head.x - (sizeShip - 1)] == 0)
							flag = false;

					break;
				}
		}
	}

	bool checkKillShip(int x, int y)  //(x, y) - coordinats shot and hit
	{
		//Top and bottom, vertical
		if ((checkCoordinate(x, y - 1) && (field[y - 1][x] == CellStatus::WOUNDED || field[y - 1][x] == CellStatus::SHIP)) || (checkCoordinate(x, y + 1) && (field[y + 1][x] == CellStatus::WOUNDED || field[y + 1][x] == CellStatus::SHIP)))
		{
			int amountBottom = 0, amountTop = 0;
			bool isKill = true;

			for (int i = y + 1; ; i++) {
				if (!checkCoordinate(x, i) || field[i][x] == CellStatus::EMTY || field[i][x] == CellStatus::PAST)
					break;

				else if (field[i][x] == CellStatus::WOUNDED)
					amountBottom += 1;

				else if (field[i][x] == CellStatus::SHIP) {
					isKill = false;
					break;
				}
			}

			for (int i = y - 1; ; i--) {
				if (!checkCoordinate(x, i) || field[i][x] == CellStatus::EMTY || field[i][x] == CellStatus::PAST)
					break;

				else if (field[i][x] == CellStatus::WOUNDED)
					amountTop += 1;

				else if (field[i][x] == CellStatus::SHIP) {
					isKill = false;
					break;
				}
			}

			if (isKill) {
				for (int i = y; i <= y + amountBottom; i++)
					field[i][x] = CellStatus::KILL;

				for (int i = y; i >= y - amountTop; i--)
					field[i][x] = CellStatus::KILL;

				return true;
			}
		}

		//Right and left, horizontal
		else if ((checkCoordinate(x + 1, y) && (field[y][x + 1] == CellStatus::WOUNDED || field[y][x + 1] == CellStatus::SHIP)) || (checkCoordinate(x - 1, y) && (field[y][x - 1] == CellStatus::WOUNDED || field[y][x - 1] == CellStatus::SHIP)))
		{
			int amountRight = 0, amountLeft = 0;
			bool isKill = true;

			for (int i = x + 1; ; i++) {
				if (!checkCoordinate(i, y) || field[y][i] == CellStatus::EMTY || field[y][i] == CellStatus::PAST)
					break;

				else if (field[y][i] == CellStatus::WOUNDED)
					amountRight += 1;

				else if (field[y][i] == CellStatus::SHIP) {
					isKill = false;
					break;
				}
			}

			for (int i = x - 1; ; i--) {
				if (!checkCoordinate(i, y) || field[y][i] == CellStatus::EMTY || field[y][y] == CellStatus::PAST)
					break;

				else if (field[y][i] == CellStatus::WOUNDED)
					amountLeft += 1;

				else if (field[y][i] == CellStatus::SHIP) {
					isKill = false;
					break;
				}
			}

			if (isKill) {
				for (int i = x; i <= x + amountRight; i++)
					field[y][i] = CellStatus::KILL;

				for (int i = x; i >= x - amountLeft; i--)
					field[y][i] = CellStatus::KILL;

				return true;
			}
		}

		else {
			field[y][x] = CellStatus::KILL;
			return true;
		}

		return false;
	}

	void arrangeShip(int &route, sb::Coordinate &head, int sizeShip)
	{
		switch (route)
		{
		case RoutesShip::TOP:
			for (int i = head.y; i > head.y - sizeShip; i--) {
				field[i][head.x] = CellStatus::SHIP;
				surroundCell(head.x, i);
			}

			break;

		case RoutesShip::RIGHT:
			for (int i = head.x; i < head.x + sizeShip; i++) {
				field[head.y][i] = CellStatus::SHIP;
				surroundCell(i, head.y);
			}

			break;

		case RoutesShip::BOTTOM:
			for (int i = head.y; i < head.y + sizeShip; i++) {
				field[i][head.x] = CellStatus::SHIP;
				surroundCell(head.x, i);
			}

			break;

		case RoutesShip::LEFT:
			for (int i = head.x; i > head.x - sizeShip; i--) {
				field[head.y][i] = CellStatus::SHIP;
				surroundCell(i, head.y);
			}

			break;
		}
	}

public:
	void setShips() {
		zeroingArray();
		amountWounded = 0;

		setFourShipDeck();
		setThreeShipDeck();
		setTwoShipDeck();
		setOneShipDeck();

		replaceEnvironment();
	}

	bool checkCoordinate(int x, int y) { //check coordinate position
		if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
			return false;

		else
			return true;
	}

	static enum RoutesShip {
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
	};

	static enum CellStatus {
		EMTY,
		SHIP,
		WOUNDED,
		KILL,
		PAST
	};

	FieldBattle() {
		field = new int* [HEIGHT];
		amountWounded = 0;

		for (int i = 0; i < HEIGHT; i++)
			field[i] = new int[WIDTH];

		setShips();
	}

	~FieldBattle() {
		for (int i = 0; i < HEIGHT; i++)
			delete[] field[i];

		delete[] field;
	}

	int** getField() {
		return field;
	}

	static int randomGenerate(int upperBound) {
		return rand() % upperBound;
	}

	static enum ResultShot {
		NOT_ALLOWED_SHOT,
		HIT_SHOT,
		PAST_SHOT,
		KILL_SHOT,
		SHIP_ALREADY_WAS_WOUNDED_SHOT
	};

	int shot(int x, int y)  //0 - error shot, 1 - hit, 2 - past, 3 - kill, 4 - ship was already wounded
	{
		if (checkCoordinate(x, y))
		{
			if (field[y][x] == CellStatus::EMTY) {
				field[y][x] = CellStatus::PAST;  //past

				return ResultShot::PAST_SHOT;
			}

			else if (field[y][x] == CellStatus::PAST || field[y][x] == CellStatus::KILL)
				return ResultShot::NOT_ALLOWED_SHOT;

			else if (field[y][x] == CellStatus::WOUNDED)
				return ResultShot::SHIP_ALREADY_WAS_WOUNDED_SHOT;

			else if (field[y][x] == CellStatus::SHIP) { //check on kill ship
				amountWounded += 1;
				field[y][x] = CellStatus::WOUNDED;

				if (checkKillShip(x, y))
					return ResultShot::KILL_SHOT;
				
				return ResultShot::HIT_SHOT;
			}
		}

		else
			return ResultShot::NOT_ALLOWED_SHOT;
	}

	bool isAllKill() {
		return (amountWounded == 20 ? true : false);
	}

	void print()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				std::cout << field[i][j] << " ";

			std::cout << std::endl;
		}
	}
};

/*class IIComputer
{
private:
	FieldBattle userField;
	bool isHit = false;
	int x, y;
	int resultShot;
	int routeShot = 1;  //1 - top or right, 2 - bottom or left

	enum RoutesShip {
		NONE,
		HORIZONTAL,
		VERTICAL
	};

	RoutesShip routeShip = RoutesShip::NONE;  //0 - not route, 1 - horizontal, 2 - vertical

public:
	IIComputer(FieldBattle& userField) {
		this->userField = userField;
	}

	int run()  //one step
	{
		std::cout << "isRun" << " isHit = " << isHit << std::endl;

		if (!isHit) { //пытается ранить корабль
			routeShot = 1;

			do {
				x = userField.randomGenerate(10);
				y = userField.randomGenerate(10);
				resultShot = userField.shot(x, y);
			}
			while (resultShot == 0);

			std::cout << "resultShot = " << resultShot << "  x = " << x << " Y = " << y << std::endl;

			if (resultShot == 1)  //hit
				isHit = true;
		}

		else { //добивает
			if (routeShip == RoutesShip::NONE)  //направление корабля неизвестно, то выстреливаем в поисках направления
			{
				std::cout << "routeShip = NONE" << std::endl;

				if ((userField.checkCoordinate(x, y - 1) && (resultShot = userField.shot(x, y - 1)) != 0) || (userField.checkCoordinate(x, y + 1) && (resultShot = userField.shot(x, y + 1)) != 0))  //Top or bottom
					if (resultShot == 1)  //hit
						routeShip = RoutesShip::VERTICAL;

				else if ((userField.checkCoordinate(x + 1, y) && (resultShot = userField.shot(x + 1, y)) != 0) || (userField.checkCoordinate(x - 1, y) && (resultShot = userField.shot(x - 1, y)) != 0))  //Right or left
					if (resultShot == 1)  //hit
						routeShip = RoutesShip::HORIZONTAL;

				if (resultShot == 3)
					isHit = false;

				std::cout << "routeShip = " << routeShip << std::endl;
			}

			else if (routeShip == RoutesShip::VERTICAL)
			{
				if (routeShot == 1)
					for (int i = y; ; i--)
						if (userField.checkCoordinate(x, i))
						{
							resultShot = userField.shot(x, i);

							if (resultShot == 0) {
								routeShot = 2;
								break;
							}

							else if (resultShot == 4)
								continue;

							else if (resultShot == 3) {
								isHit = false;
								break;
							}
						}

						else
							routeShot = 2;

				else if (routeShot == 2)
					for (int i = y; ; i++)
						if (userField.checkCoordinate(x, i))
						{
							resultShot = userField.shot(x, i);

							if (resultShot == 0) {
								routeShot = 1;
								break;
							}

							else if (resultShot == 4)
								continue;

							else if (resultShot == 3) {
								isHit = false;
								break;
							}
						}

						else
							routeShot = 1;
			}

			else if (routeShip == RoutesShip::HORIZONTAL)
			{
				if (routeShot == 1)
					for (int i = x; ; i++)
						if (userField.checkCoordinate(x, i))
						{
							resultShot = userField.shot(x, i);

							if (resultShot == 0) {
								routeShot = 2;
								break;
							}

							else if (resultShot == 4)
								continue;

							else if (resultShot == 3) {
								isHit = false;
								break;
							}
						}

						else
							routeShot = 2;

				else if (routeShot == 2)
					for (int i = x; ; i--)
						if (userField.checkCoordinate(x, i))
						{
							resultShot = userField.shot(x, i);

							if (resultShot == 0) {
								routeShot = 1;
								break;
							}

							else if (resultShot == 4)
								continue;

							else if (resultShot == 3) {
								isHit = false;
								break;
							}
						}

						else
							routeShot = 1;
			}
		}

		std::cout << "resultShot(return) = " << resultShot << std::endl;
		return resultShot;
	}
};*/

class IIComputer
{
private:
	FieldBattle userField;
	bool isHit;
	int xShot, yShot;

	enum RoutesShip {
		NONE,
		HORIZONTAL,
		VERTICAL
	};

	RoutesShip routeShip;

public:
	IIComputer(FieldBattle& userField) : isHit{ false }, routeShip{RoutesShip::NONE} {
		this->userField = userField;
	}

	int run()  //one step computer
	{
		int resultShot;

		if (isHit) {
			if (routeShip == RoutesShip::NONE)
			{
				int routeShot = FieldBattle::randomGenerate(4);

				while (true)
				{
					switch (routeShot)
					{
					case 0:  //TOP
						resultShot = userField.shot(xShot, yShot - 1);
						break;
					case 1:  //RIGHT
						resultShot = userField.shot(xShot + 1, yShot);
						break;
					case 2:  //BOTTOM
						resultShot = userField.shot(xShot, yShot + 1);
						break;
					case 3:  //LEFT
						resultShot = userField.shot(xShot - 1, yShot);
						break;
					}

					if (resultShot == FieldBattle::ResultShot::NOT_ALLOWED_SHOT) {
						routeShot = FieldBattle::randomGenerate(4);
						continue;
					}

					else if (resultShot == FieldBattle::ResultShot::PAST_SHOT)
						break;

					else if (resultShot == FieldBattle::ResultShot::HIT_SHOT) {
						switch (routeShot)
						{
						case 0 && 2:
							routeShip = RoutesShip::VERTICAL;
							break;
						case 1 && 3:
							routeShip = RoutesShip::HORIZONTAL;
							break;
						}

						break;
					}

					else if (resultShot == FieldBattle::ResultShot::KILL_SHOT) {
						isHit = false;
						break;
					}
				}
			}

			else if (routeShip == RoutesShip::VERTICAL)
			{
				
			}

			else if (routeShip == RoutesShip::HORIZONTAL)
			{
				
			}

			//std::cout << routeShip << std::endl;
		}

		else { //пытается ранить корабль
			do {
				xShot = userField.randomGenerate(10);
				yShot = userField.randomGenerate(10);
				resultShot = userField.shot(xShot, yShot);
			} while (resultShot == FieldBattle::ResultShot::NOT_ALLOWED_SHOT || resultShot == FieldBattle::ResultShot::SHIP_ALREADY_WAS_WOUNDED_SHOT);

			if (resultShot == FieldBattle::ResultShot::HIT_SHOT)  //hit
				isHit = true;
		}

		return resultShot;
	}
};

int main()
{
	srand(time(0));
	using namespace sf;

	RenderWindow window(VideoMode(900, 650), "See battle", Style::Close);

	sb::Sprite fon("pictures/fon.jpg", { 0, 0 });
	sb::Buttons::Button buttonExit{ "pictures/buttons/exit_button/exit.png", "pictures/buttons/exit_button/exit_mouse_moved.png", "pictures/buttons/exit_button/exit_press.png", {530, 510} };
	sb::Bounds boundsExit = buttonExit.getBounds();
	sb::Buttons::Button buttonNewGame{ "pictures/buttons/new_game_button/new_game.png", "pictures/buttons/new_game_button/new_game_mouse_moved.png", "pictures/buttons/new_game_button/new_game_press.png", {130, 510} };
	sb::Bounds boundsNewGame = buttonNewGame.getBounds();

	sb::Sprite ship("pictures/ships/ship.png", { 0, 0 });
	sb::Sprite shipWounded("pictures/ships/wounded_ship.png", { 0, 0 });
	sb::Sprite shipKill("pictures/ships/kill_ship.png", { 0, 0 });
	sb::Sprite bomb("pictures/bomb.jpeg", { 0, 0 });

	sb::Sprite cursor("pictures/cursor.png", { 0, 0 });

	sb::Text textComputer{ "Computer", {150, 20}, Color::Blue, 40 };
	sb::Text textPlayer{ "Player", {590, 20}, Color::Blue, 40 };
	sb::Text textRun{ "Running: ", {300, 440}, Color::Blue, 40};

	bool isRun = true;  //true - player, false - computer
	bool isCursor = false;  //true - on field, false - not on field
	//bool isWinner;

	FieldBattle userField{};
	FieldBattle computerField{};

	IIComputer computerII{userField};

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event)) {
			buttonNewGame.setStatus(sb::Buttons::StatusButton::BUTTON);
			buttonExit.setStatus(sb::Buttons::StatusButton::BUTTON);
			Vector2i mousePosition = Mouse::getPosition(window);
			isCursor = false;  //true - cursor mouse in field

			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::MouseMoved:
				if (mousePosition.x > boundsNewGame.pos.x&& mousePosition.x < boundsNewGame.size.x && mousePosition.y > boundsNewGame.pos.y && mousePosition.y < boundsNewGame.size.y)
					buttonNewGame.setStatus(sb::Buttons::StatusButton::BUTTON_MOUSE_MOVED);

				else if (mousePosition.x > boundsExit.pos.x&& mousePosition.x < boundsExit.size.x && mousePosition.y > boundsExit.pos.y&& mousePosition.y < boundsExit.size.y)
					buttonExit.setStatus(sb::Buttons::StatusButton::BUTTON_MOUSE_MOVED);

				else if (mousePosition.x > 100 && mousePosition.x < 400 && mousePosition.y > 100 && mousePosition.y < 400) {
					cursor.setPosition(100 + ((mousePosition.x - 100) / 30) * 30, 101 + ((mousePosition.y - 100) / 30) * 30);
					isCursor = true;
				}

				break;

			case Event::MouseButtonPressed:
				if (mousePosition.x > boundsNewGame.pos.x&& mousePosition.x < boundsNewGame.size.x && mousePosition.y > boundsNewGame.pos.y&& mousePosition.y < boundsNewGame.size.y) {
					buttonNewGame.setStatus(sb::Buttons::StatusButton::BUTTON_PRESS);
					userField.setShips();
					computerField.setShips();
				}

				else if (mousePosition.x > boundsExit.pos.x&& mousePosition.x < boundsExit.size.x 
					&& mousePosition.y > boundsExit.pos.y&& mousePosition.y < boundsExit.size.y) {
					buttonExit.setStatus(sb::Buttons::StatusButton::BUTTON_PRESS);
					window.close();
				}

				else if (mousePosition.x > 100 && mousePosition.x < 400 && mousePosition.y > 100 && mousePosition.y < 400)
					if (isRun) {
						int resultShot = computerField.shot((mousePosition.x - 100) / 30, (mousePosition.y - 100) / 30);

						if (resultShot == FieldBattle::ResultShot::PAST_SHOT
							|| resultShot == FieldBattle::ResultShot::NOT_ALLOWED_SHOT
							|| resultShot == FieldBattle::ResultShot::SHIP_ALREADY_WAS_WOUNDED_SHOT) {
							isRun = false;  //running computer
							//computerField.print();
						}
					}

				break;
			}
		}

		//std::cout << "for debug" << std::endl;

		window.clear(Color::Black);

		//draw content

		window.draw(fon);

		window.draw(textComputer);
		window.draw(textPlayer);

		if (isRun)
			textRun.setString("Run: player");

		else
			textRun.setString("Run: computer");

		if (isCursor)
			window.draw(cursor);

		//run computer
		if (!isRun) {
			std::cout << "run Computer" << std::endl;
			int computerResultShot = computerII.run();

			if (computerResultShot == FieldBattle::ResultShot::PAST_SHOT)
				isRun = true;
		}

		window.draw(textRun);

		window.draw(buttonExit.getSprite());
		window.draw(buttonNewGame.getSprite());

		for (int i = 0; i <= 10; i++) {
			window.draw(sb::getLine(100 + i * 30, 100, 100 + i * 30, 400, Color::Black));
			window.draw(sb::getLine(100, 100 + i * 30, 400, 100 + i * 30, Color::Black));

			window.draw(sb::getLine(500 + i * 30, 100, 500 + i * 30, 400, Color::Black));
			window.draw(sb::getLine(500, 100 + i * 30, 800, 100 + i * 30, Color::Black));
		}

		int** userArray = userField.getField();

		for (int i = 0; i < userField.HEIGHT; i++)
			for (int j = 0; j < userField.WIDTH; j++)
				switch (userArray[i][j]) {
				case 1:  //ship
					ship.setPosition(500 + j * 30, 101 + i * 30);
					window.draw(ship);
					break;

				case 2:  //wounded ship
					shipWounded.setPosition(500 + j * 30, 101 + i * 30);
					window.draw(shipWounded);
					break;

				case 3:  //kill ship
					shipKill.setPosition(500 + j * 30, 101 + i * 30);
					window.draw(shipKill);
					break;

				case 4:  //was short
					bomb.setPosition(500 + j * 30, 101 + i * 30);
					window.draw(bomb);
					break;
				}

		int** computerArray = computerField.getField();

		for (int i = 0; i < computerField.HEIGHT; i++)
			for (int j = 0; j < computerField.WIDTH; j++)
				switch (computerArray[i][j]) {
				case 2:  //wounded ship
					shipWounded.setPosition(100 + j * 30, 101 + i * 30);
					window.draw(shipWounded);
					break;

				case 3:  //kill ship
					shipKill.setPosition(100 + j * 30, 101 + i * 30);
					window.draw(shipKill);
					break;

				case 4:  //was short
					bomb.setPosition(100 + j * 30, 101 + i * 30);
					window.draw(bomb);
					break;
				}

		window.display();
	}

	return 0;
}