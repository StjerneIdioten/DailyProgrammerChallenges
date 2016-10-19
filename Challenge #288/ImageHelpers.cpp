#include "ImageHelpers.h"
#include <cmath>

std::vector<ImageHelpers::Pixel> ImageHelpers::getNeighbours(rw::sensor::Image* img, ImageHelpers::Pixel p)
{
	return getNeighbours(img, p, 1);
}

std::vector<ImageHelpers::Pixel> ImageHelpers::getNeighbours(rw::sensor::Image* img, ImageHelpers::Pixel p, unsigned int radius)
{
	std::vector<ImageHelpers::Pixel> neighbours;
	neighbours.reserve(pow((1 + (2 * radius)), 2) - 1);

	for (int i = (0 - radius); i <= (0 + radius); i++)
	{
		for (int j = (0 - radius); j <= (0 + radius); j++)
		{
			if (!(i == 0 && j == 0))
			{
				if ((p.x + i >= 0 && p.x + i <= img->getWidth()) && (p.y + j >= 0 && p.y + j <= img->getHeight()))
				{
					neighbours.push_back(Pixel(p.x + i, p.y + j, img->getPixelValuei(p.x + i, p.y + j, 0)));
				}
			}
		}
	}
	return neighbours;
}

ImageHelpers::Pixel ImageHelpers::getNeighbourSmallest(rw::sensor::Image* img, ImageHelpers::Pixel p)
{
	std::vector<ImageHelpers::Pixel> neighbours = getNeighbours(img, p);

	int valueSmallest = 255;

	for (ImageHelpers::Pixel pix : neighbours)
	{
		if (pix.value < valueSmallest) valueSmallest = pix.value;
	}

	return Pixel(p.x, p.y, valueSmallest);
}

void ImageHelpers::fillImage(rw::sensor::Image* img, unsigned char colour)
{
	for (int i = 0; i < img->getWidth(); i++)
	{
		for (int j = 0; j < img->getHeight(); j++)
		{
			img->setPixel8U(i, j, colour);
		}
	}
}

void ImageHelpers::clearImage(rw::sensor::Image* img)
{
	fillImage(img, 255);
}

void ImageHelpers::drawDot(rw::sensor::Image* img, Pixel p, int radius, int colour)
{

	Pixel centerPixel = Pixel(radius, radius);

	for (int i = 0; i < 2 * radius; i++)
	{
		for (int j = 0; j < 2 * radius; j++)
		{
			if (sqrt(pow(centerPixel.x - i, 2) + pow(centerPixel.y - j, 2)) < radius)
			{
				img->setPixel8U((p.x - radius) + i, (p.y - radius) + j, colour);
			}
		}
	}
}

/*
void ImageHelpers::drawDot(rw::sensor::Image* img, Pixel p, int radius, int colour, bool border)
{
	if (border) 
	{
		rw::sensor::Image* borderImg = new rw::sensor::Image(radius * 2, radius * 2, rw::sensor::Image::GRAY, rw::sensor::Image::Depth8U);
		clearImage(borderImg);
		drawDot(borderImg, Pixel(radius, radius), radius, colour);
		//drawDot(img, p, radius, colour);
		Pixel smallest;

		for (int i = 0; i < borderImg->getWidth(); i++)
		{
			for (int j = 0; j < borderImg->getHeight(); j++)
			{
				if (borderImg->getPixelValuei(i, j, rw::sensor::Image::Depth8U) != colour)
				{
					Pixel smallest = getNeighbourSmallest(borderImg, Pixel(i, j));
					if (smallest.value != 255) 
					{
						img->setPixel8U((p.x - radius) + i, (p.y - radius) + j, 0);
					}
				}
				
			}
		}

	}
	else 
	{
		drawDot(img, p, radius, colour);
	}

}
*/