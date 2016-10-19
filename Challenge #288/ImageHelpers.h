#pragma once
#include <vector>
#include "Image.hpp"

class ImageHelpers
{
public:

	struct Pixel;

	ImageHelpers();

	static std::vector<Pixel> getNeighbours(rw::sensor::Image* img, Pixel p);
	static std::vector<Pixel> getNeighbours(rw::sensor::Image* img, Pixel p, unsigned int radius);
	static void clearImage(rw::sensor::Image* img);
	static void fillImage(rw::sensor::Image* img, unsigned char colour);

	//Graphics stuff
	static void drawDot(rw::sensor::Image* img, Pixel p, int radius, int colour);
	//static void drawDot(rw::sensor::Image* img, Pixel p, int radius, int colour, bool border);

	static Pixel getNeighbourSmallest(rw::sensor::Image* img, Pixel p);

private:

};

struct ImageHelpers::Pixel
{
	inline Pixel() : x(0), y(0), value(255) {};
	inline Pixel(int x, int y) : x(x), y(y), value(255) {};
	inline Pixel(int x, int y, int value) : x(x), y(y), value(value) {};
	int x;
	int y;
	int value;
};