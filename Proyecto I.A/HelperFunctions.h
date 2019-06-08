#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <array>
#include "CVector2D.h"
///Forward declaration 
static void WindowEvents(sf::RenderWindow & window, bool& isWindowRuning);

/*! To see the values of the vectors */
static std::ostream& operator<<(std::ostream& OutputStream, const CVector2D& Vector)
{
	OutputStream << "< " << Vector.GetX() << ", " << Vector.GetY() << ">";
	return OutputStream;
}

static void DumbStop()
{
	std::cin.ignore();
	std::cin.get();
}
// selects random position 
static CVector2D RandomPos(int UpperLimitX, int UpperLimitY, int LowerLimitX = 1, int LowerLimitY = 1)
{
	std::array<CVector2D, 5> RandomPositions;

	RandomPositions[0] = CVector2D(-LowerLimitX, LowerLimitY);
	RandomPositions[1] = CVector2D(UpperLimitX, UpperLimitY);
	RandomPositions[2] = CVector2D(UpperLimitX, -LowerLimitY);
	RandomPositions[3] = CVector2D(-LowerLimitX, UpperLimitY);
	RandomPositions[4] = CVector2D(UpperLimitX / 2, UpperLimitY / 2);

	std::random_device randDevice;

	std::mt19937 randResult(randDevice());

	std::shuffle(RandomPositions.begin(), RandomPositions.end(), randResult);

	return	RandomPositions[0];
}
// for converting degrees to radians (because it easier to think in degrees)
static float ConvertDegreesToRadians(float Degrees)
{
	return Degrees * (3.14159f / 180.0f);
}

template<class T>
static bool isWithinVectorBounds(int Index, std::vector<T> &Vec)
{
	if (Index > Vec.size() - 1 || Index < 0)
	{
		return false;
	}
	return true;
}


static void WindowEvents(sf::RenderWindow & window, bool& isWindowRuning)
{
	sf::Event PosibleEvent;

	if (window.pollEvent(PosibleEvent))
	{
		switch (PosibleEvent.type)
		{
		case(sf::Event::Closed):
			window.close();
			isWindowRuning = false;
			break;
		case(sf::Event::KeyPressed):
			if (PosibleEvent.type == sf::Keyboard::F4)
			{
				window.close();
				isWindowRuning = false;
			}
			break;
		}
	}
}

static void WindowEvents(sf::RenderWindow & window, bool& isWindowRuning, CVector2D &Position)
{
	sf::Event MY_Event;
	while (window.pollEvent(MY_Event))
	{
		switch (MY_Event.type)
		{

		case(sf::Event::MouseMoved):
			Position.SetX(MY_Event.mouseMove.x);
			Position.SetY(MY_Event.mouseMove.y);
		case(sf::Event::KeyPressed):
			if (MY_Event.type == sf::Keyboard::F4)
			{
				window.close();
				isWindowRuning = false;
			}
			break;
		case(sf::Event::Closed):
			window.close();
			isWindowRuning = false;
		default:
			break;
		}

	}
}