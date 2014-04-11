/////////////////////////////////////////////////////////// 
//														 //	
//	Class: CheckPatterns.cpp 						  	 // 
//													  	 //
//	Auther's: 										  	 //
//	Thomas                    						  	 //
//  Kevin                                             	 //
//  Mitchell                                          	 //
//  Wouter                                             	 //
//	                                                   	 //
//	Date:                                              	 //
//	3-4-14'                                            	 //
//	                                                   	 //
//	Version:                                           	 //
//	V0.1.                                              	 //
//                                                       //
//	Description:                                         //
//	The CheckPatterns class consist of varius algorithm  //
//	to check numbers and characters on there paterns.    //
//                                                       //
///////////////////////////////////////////////////////////                                      

#include "CheckPatterns.h"

CheckPatterns::CheckPatterns()
{
	//bt = new BaseTimer();
}

CheckPatterns::~CheckPatterns()
{
	//delete bt;
}

// =======================================================================================

/**
* checkBlackWhiteTransisitionVertical will look for transisiton in an ImageGray on the Vertical axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::checkPixelsPerLineHorizontal(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();

	if (percentage > 100)
	{
		percentage = 100;
	}
	else if (percentage < 0)
	{
		percentage = 0;
	}

	//int y = (int)(sourceImage.height() / 100.0 * percentage);
	int y = Extensions::getValueFromPercentage(sourceImage.height(), percentage);
	//int y = Extensions::getPercentage(percentage, sourceImage.height());
	int blackPixels = 0;

	for (int x = sourceImage.width() - 1; x >= 0; x--)
	{
		if (*(sourceImage.data(x, y)) > thresholdValue)
		{
			blackPixels++;
		}
	}

	//bt->stop();
	//std::cout << "Time for the checkPixelsPerLineHorizontal function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;

	//return blackPixels;
	//return (int)(blackPixels / (double)(sourceImage.width()) * 100);
	//std::cout << "blackpixels: " << blackPixels << " sourceImg Width: " << sourceImage.width() << " percentage: " << Extensions::getPercentage(blackPixels, sourceImage.width()) << std::endl;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(blackPixels, sourceImage.width()));
}

/**
* checkBlackWhiteTransisitionVertical will look for transisiton in an ImageGray on the Vertical axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::checkPixelsPerLineVertical(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();

	if (percentage > 100)
	{
		percentage = 100;
	}
	else if (percentage < 0)
	{
		percentage = 0;
	}

	//int x = (int)(sourceImage.width() / 100.0 * percentage);
	int x = Extensions::getValueFromPercentage(sourceImage.width(), percentage);
	int blackPixels = 0;

	for (int y = sourceImage.height() - 1; y >= 0; y--)
	{
		if (*(sourceImage.data(x, y)) > thresholdValue)
		{
			blackPixels++;
		}
	}

	//bt->stop();
	//std::cout << "Time for the checkPixelsPerLineVertical function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;

	//return blackPixels;
	//return (int)(blackPixels / (double)(sourceImage.height()) * 100);
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(blackPixels, sourceImage.height()));
}

// =======================================================================================

/**
* checkBlackWhiteTransisitionHorizontal will look for transisiton in an ImageGray on the horizontal axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::checkBlackWhiteTransisitionHorizontal(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();

	//int y = (int)(sourceImage.height() / 100.0 * percentage);
	int y = Extensions::getValueFromPercentage(sourceImage.height(), percentage);
	int pixelCounter = 0;
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	int oldPixel = 1;
	char currentPixel = 0;


	for (int x = sourceImage.width() - 1; x >= 0; x--)
	{

		if (*(sourceImage.data(x, y)) > thresholdValue)
		{

			currentPixel = 1.0;
		}
		else
		{
			currentPixel = 0.0;
		}

		if (currentPixel != oldPixel)
		{
			pixelCounter++;
			oldPixel = currentPixel;
		}
	}

	//bt->stop();
	//std::cout << "Time for the checkBlackWhiteTransision function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return pixelCounter;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(pixelCounter, percentage));
}

/**
* checkBlackWhiteTransisitionVertical will look for transisiton in an ImageGray on the Vertical axis. These transitions are made from
* black to white or white to black. If a transisition is detected a counter will be increased.
*
* @param  sourceImage
* @param  percentage
* @return
*/

double CheckPatterns::checkBlackWhiteTransisitionVertical(const ImageGray &sourceImage, int percentage)
{
	//bt->reset();
	//bt->start();
	int x = Extensions::getValueFromPercentage(sourceImage.width(), percentage);
	int pixelCounter = 0;
	char currentPixel = 0;
	// set oldpixel to 1 because white is 1 and every ImageGray starts with white
	int oldPixel = 1;

	for (int y = sourceImage.height() - 1; y >= 0; y--)
	{
		if (*(sourceImage.data(x, y)) > thresholdValue)
		{
			currentPixel = 1;
		}
		else
		{
			currentPixel = 0;
		}

		if (currentPixel != oldPixel)
		{
			pixelCounter++;
			oldPixel = currentPixel;
		}
	}

	//bt->stop();
	//std::cout << "Time for the checkBlackWhiteTransision function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return pixelCounter;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(pixelCounter, percentage));
}

// =======================================================================================

double CheckPatterns::checkSymmetryHorizontal(const ImageGray &sourceImage, bool boundingBox)
{
	//bt->reset();
	//bt->start();
	int numberOfBlackPixels = 0, symmetricBlackPixels = 0;
	//double percentageSymmetric;
	if (boundingBox)
	{
		int x1 = this->findLeftBlackPixel(sourceImage);
		int x2 = this->findRightBlackPixel(sourceImage);
		int y1 = this->findTopBlackPixel(sourceImage);
		int y2 = this->findBottomBlackPixel(sourceImage);
		for (int y = y2; y >= y1; y--)
		{
			for (int x = x2; x >= ((x2 - x1) / 2); x--)
			{
				if (*(sourceImage.data(x, y)) < thresholdValue)
				{
					numberOfBlackPixels++;
					if (*(sourceImage.data(sourceImage.width() - x, y)) < thresholdValue)
					{
						symmetricBlackPixels++;
					}
				}
			}
		}
	}
	else
	{
		for (int y = sourceImage.height(); y >= 0; y--)
		{
			for (int x = sourceImage.width(); x >= (sourceImage.width() / 2); x--)
			{
				if (*(sourceImage.data(x, y)) < thresholdValue)
				{
					numberOfBlackPixels++;
					if (*(sourceImage.data(sourceImage.width() - x, y)) < thresholdValue)
					{
						symmetricBlackPixels++;
					}
				}
			}
		}
	}
	//percentageSymmetric = ((double)symmetricBlackPixels / (double)numberOfBlackPixels)*100.0;
	//bt->stop();
	//std::cout << "Time for the checkSymmetryHorizontal function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return (int)percentageSymmetric;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(symmetricBlackPixels, numberOfBlackPixels));
}

double CheckPatterns::checkSymmetryVertical(const ImageGray &sourceImage, bool boundingBox)
{
	//bt->reset();
	//bt->start();
	int numberOfBlackPixels = 0, symmetricBlackPixels = 0;
	//double percentageSymmetric;
	if (boundingBox)
	{
		int x1 = this->findLeftBlackPixel(sourceImage);
		int x2 = this->findRightBlackPixel(sourceImage);
		int y1 = this->findTopBlackPixel(sourceImage);
		int y2 = this->findBottomBlackPixel(sourceImage);
		for (int y = y2; y >= ((y2 - y1) / 2); y--)
		{
			for (int x = x2; x >= x1; x--)
			{
				if (*(sourceImage.data(x, y)) < thresholdValue)
				{
					numberOfBlackPixels++;
					if (*(sourceImage.data(x, sourceImage.height() - y)) < thresholdValue)
					{
						symmetricBlackPixels++;
					}
				}
			}
		}
	}
	else
	{
		for (int y = sourceImage.height(); y >= (sourceImage.height() / 2); y--)
		{
			for (int x = sourceImage.width(); x >= 0; x--)
			{
				if (*(sourceImage.data(x, y)) < thresholdValue)
				{
					numberOfBlackPixels++;
					if (*(sourceImage.data(x, sourceImage.height() - y)) < thresholdValue)
					{
						symmetricBlackPixels++;
					}
				}
			}
		}
	}
	//percentageSymmetric = ((double)symmetricBlackPixels / (double)numberOfBlackPixels)*100.0;
	//bt->stop();
	//std::cout << "Time for the checkSymmetryVertical function: " << //bt->elapsedMicroSeconds() << " Microseconds (" << //bt->elapsedMilliSeconds() << "ms)" << std::endl;
	//return (int)percentageSymmetric;
	return Extensions::getWeightFromPercentage(Extensions::getPercentage(symmetricBlackPixels, numberOfBlackPixels));
}

int CheckPatterns::findLeftBlackPixel(const ImageGray &sourceImage)
{
	int xValue = sourceImage.width();
	for (int y = sourceImage.height(); y >= 0; y--)
	{
		for (int x = 0; x <= (sourceImage.width() / 2); x++)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (x <= xValue){
					xValue = x;
					x = 0;
					y--;
				}
			}
		}
	}
	return xValue;
}

int CheckPatterns::findRightBlackPixel(const ImageGray &sourceImage)
{
	int xValue = 0;
	for (int y = sourceImage.height(); y >= 0; y--)
	{
		for (int x = sourceImage.width(); x >= (sourceImage.width() / 2); x--)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (x >= xValue)
				{
					xValue = x;
					x = sourceImage.width();
					y--;
				}
			}
		}
	}
	return xValue;
}

int CheckPatterns::findTopBlackPixel(const ImageGray &sourceImage)
{
	int yValue = sourceImage.height();
	for (int x = sourceImage.width(); x >= 0; x--)
	{
		for (int y = (sourceImage.height() / 2); y <= sourceImage.height(); y++)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (y <= yValue)
				{
					yValue = y;
					x--;
					y = 0;
				}
			}
		}
	}
	return yValue;
}

int CheckPatterns::findBottomBlackPixel(const ImageGray &sourceImage)
{
	int yValue = 0;
	for (int x = sourceImage.width(); x >= 0; x--)
	{
		for (int y = sourceImage.height(); y >= (sourceImage.height() / 2); y--)
		{
			if (*(sourceImage.data(x, y)) < thresholdValue)
			{
				if (y >= yValue)
				{
					yValue = y;
					x--;
					y = 0;
				}
			}
		}
	}
	return yValue;
};