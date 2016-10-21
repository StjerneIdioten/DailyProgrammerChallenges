#include "config.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <vector>

using namespace std;

struct Point
{
	inline Point() : x(0), y(0) {};
	inline Point(int x, int y) : x(x), y(y) {};
	int x;
	int y;
};

float deg2Rad(float deg)
{
	return deg * (3.14159265f / 180);
}

float rad2Deg(float rad)
{
	return rad * (180 / 3.14159265f);
}

void drawLine(sf::Image& img, Point p1, Point p2, const sf::Color& color)
{
	float x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;

	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1)) ;

	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int yStep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++) 
	{
		if (steep)
		{
			img.setPixel(y, x, color);
		}
		else
		{
			img.setPixel(x, y, color);
		}

		error -= dy;
		if (error < 0)
		{
			y += yStep;
			error += dx;
		}
	}
}

void drawStar(sf::Image& img, unsigned int n, unsigned int size)
{
	const float angleStep = deg2Rad(360.0f / n);

	const float angleOffset = deg2Rad(90) - angleStep; //To make the tip point upwards

	cout << n << " steps of " << rad2Deg(angleStep) << " degrees" << endl;

	vector<Point> points(n);

	for (int i = 0; i < n; i++)
	{
		points[i].x = (int)(0.5f + (img.getSize().x / 2) + (size * cos((i * angleStep) - angleOffset)));
		points[i].y = (int)(0.5f + (img.getSize().y / 2) + (size * sin((i * angleStep) - angleOffset)));
	}

	if (n % 2 == 0)
	{
		for (int i = 0; i < (n - 2) / 2; i++)
		{
			drawLine(img, points[i], points[i + (n / 2) - 1], sf::Color::Black);
			drawLine(img, points[i], points[i + (n / 2) + 1], sf::Color::Black);
		}
		drawLine(img, points[(n - 2) / 2], points[points.size() - 2], sf::Color::Black);
		drawLine(img, points[n / 2], points.back(), sf::Color::Black);
	}
	else
	{
		for (int i = 0; i < n / 2; i++)
		{
			drawLine(img, points[i], points[i + (n / 2)], sf::Color::Black);
			drawLine(img, points[i], points[i + (n / 2) + 1], sf::Color::Black);
		}
		drawLine(img, points[n / 2], points.back(), sf::Color::Black);
	}
}

void drawStar(sf::Image& img, unsigned int n)
{
	drawStar(img, n, 100);
}

int main(int argc, char* argv[]) {

	cout << "Version " << myproject_VERSION_MAJOR << "." << myproject_VERSION_MINOR << endl;

	sf::Image starImage;

	starImage.create(255, 255, sf::Color::White);

	drawStar(starImage, 20);

	starImage.saveToFile("Star-Image.png");

}
