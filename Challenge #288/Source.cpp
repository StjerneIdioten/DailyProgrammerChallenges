#include <iostream>
#include <math.h>
#include <exception>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include "Point.hpp"
#include "Configuration.h"
#include "Matrix.h"
#include "Robot.hpp"
#include "Brushfire.h"
#include <stdio.h>
#include <time.h>
#include "Voronoi.h"
#include <random>

#define PI 3.14159265
#define PADDING 30

using namespace rw::sensor;
using namespace rw::loaders;

int main(int argc, char** argv) {
	std::string filename(argv[1]);

	Image* img = PPMLoader::load(filename);

	clock_t t = clock();

	Brushfire brushfire(img);

	std::cout << "Running Brushfire Algorithm: " << std::endl;

	brushfire.calculate();

	std::cout << "Saving Brushfire Image: " << std::endl;

	brushfire.saveAsPGM("WorldBurn.pgm");

	Voronoi jes;

	std::cout << "Generating Voronoi Diagram: " << std::endl;

	jes.edgeDetection(brushfire._brushFire);

	std::cout << "Saving Voronoi Image: " << std::endl;

	jes._gvd->saveAsPGM("Voronoi.pgm");

	jes._gvd->saveAsCsv("Pixelvalues");

	jes.generateGVD(brushfire._brushFire);

	jes._gvd->saveAsPGM("Voronoi3.pgm");

	brushfire._brushFire->saveAsCsv("Buskadsild");
	t = clock();

	std::cout << "It took: " << t / CLOCKS_PER_SEC << " seconds" << std::endl;

	Image* img2 = new Image(255, 255, Image::ColorCode::GRAY, Image::Depth8U);

	ImageHelpers::clearImage(img2);

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> placement(25, 230); // define the range
	std::uniform_int_distribution<> size(2, 20); // define the range
	std::uniform_int_distribution<> colour(0, 254); // define the range

	for (int i = 0; i < 10000; i++)
	{
		ImageHelpers::drawDot(img2, ImageHelpers::Pixel(placement(eng), placement(eng)), size(eng), colour(eng));
	}

	img2->saveAsPGM("ImageHelperTest.pgm");

}

/*
std::vector<Configuration> confs = { { 0, 0, 0 }, { 0,100,0 }, { 0,0,200 }, { 30,0,0 }, { 60,200,500 } };

std::cout << "\nThe size of the configuration space is: ";
Matrix configurationSpaceSize = Configuration::configurationSpaceSize(confs);

std::cout << configurationSpaceSize << std::endl;

Image* img = new Image((configurationSpaceSize[0][1] - configurationSpaceSize[0][0]) + 1 + (2 * PADDING),
(configurationSpaceSize[1][1] - configurationSpaceSize[1][0]) + 1 + (2 * PADDING),
Image::GRAY,
Image::Depth8U);

confs[0] = Configuration(0, abs(configurationSpaceSize[0][0]) + PADDING, abs(configurationSpaceSize[1][0]) + PADDING);

Robot john(img, confs);

john.executeConfSequence();

std::cout << "saving image..." << std::endl;
// save image
img->saveAsPGM("testout.pgm");

// cleanup
delete img;
*/