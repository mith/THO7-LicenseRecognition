//#include "exectimer.h"
#include <iostream>
#include <stdio.h>
#include <string>
//#include "Image.h"
#include "ImageLib.h"
#include "CheckPatterns.h"
#include "Extensions.h" 
//NeuralNetwork includes
#include "NN_Neuron.h"
#include "NN_Net.h"
#include "NN_TrainingData.h"
#include "OCRImageData.h"


int main(int argc, char *argv[]){

	// Percentage tests
	std::cout << "percentage: " << Extensions::getPercentage(0.7, 100) << std::endl;
	std::cout << "percentage from -1 to 1: " << Extensions::getWeightFromPercentage(25) << std::endl;


	// The program can take the imagename through commandline arguments, or either
	// just defining it in inputName below.
	std::string inputName = "k.jpg";
	
	/*=========================     Program parameters     =========================*/

	/*
	Read the chosen file
	*/
	if(argv[1] != nullptr) {
		inputName = argv[1];
		std::cout << "File is: " << inputName << "\n\n";
	} else {
		std::cout << "File is: " << inputName << "\n\n";
	}

	//Load the image in the Image class
	//Image originalImage(inputName);
	ImageLib::ImageGray originalImage("../Images/k.jpg");

	// Algorithm tests
	CheckPatterns cp;
	std::cout << "PPL H30: " << cp.checkPixelsPerLineHorizontal(originalImage, 30) << std::endl;
	std::cout << "PPL H50: " << cp.checkPixelsPerLineHorizontal(originalImage, 50) << std::endl;
	std::cout << "PPL H80: " << cp.checkPixelsPerLineHorizontal(originalImage, 80) << std::endl;
	std::cout << "PPL V30: " << cp.checkPixelsPerLineVertical(originalImage, 30) << std::endl;
	std::cout << "PPL V50: " << cp.checkPixelsPerLineVertical(originalImage, 50) << std::endl;
	std::cout << "PPL V80: " << cp.checkPixelsPerLineVertical(originalImage, 80) << std::endl;

	std::cout << std::endl;

	std::cout << "Vertical Symmetry: " << cp.checkSymmetryVertical(originalImage) << std::endl;
	std::cout << "Horizontal Symmetry: " << cp.checkSymmetryHorizontal(originalImage) << std::endl;
	
	std::cout << std::endl;

	std::cout << "BWT H30: " << cp.checkBlackWhiteTransisitionHorizontal(originalImage, 30) << std::endl;
	std::cout << "BWT H50: " << cp.checkBlackWhiteTransisitionHorizontal(originalImage, 50) << std::endl;
	std::cout << "BWT H80: " << cp.checkBlackWhiteTransisitionHorizontal(originalImage, 80) << std::endl;
	std::cout << "BWT V30: " << cp.checkBlackWhiteTransisitionVertical(originalImage, 30) << std::endl;
	std::cout << "BWT V50: " << cp.checkBlackWhiteTransisitionVertical(originalImage, 50) << std::endl;
	std::cout << "BWT V80: " << cp.checkBlackWhiteTransisitionVertical(originalImage, 80) << std::endl;

	//Save the original image
	//originalImage.SaveImageToFile("ORIGINAL_");
	std::cout << std::endl;


	// ================================================================================================
	// ================================================================================================
	// NeuralNetwork test met OCR

	OCRImageData traingData;

	// e.g., { 14, 30, 37 }
	std::vector<unsigned> topology;
	traingData.getTopology(topology);

	NN_Net myNet(topology);
	//NN_Net myNet("../Export/net.txt");

	int numberOfImages = traingData.getImageList();


	std::vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;
	int currentImage = 0;

	std::cout << "Please wait..." << std::endl;

	//Train
	srand(0);
	while(trainingPass < 500 * 1000) {
		++trainingPass;
		//currentImage = trainingPass % numberOfImages;
		currentImage = (rand() * (int)(numberOfImages) / RAND_MAX);

		if(traingData.getNextInputs(inputVals, currentImage) != topology[0]) {
			break;
		}

		myNet.feedForward(inputVals);

		myNet.getResults(resultVals);

		traingData.getTargetOutputs(targetVals, currentImage);

		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);
	}

	//Test
	trainingPass = 0;
	while(trainingPass < 30) {
		++trainingPass;
		currentImage = trainingPass % numberOfImages;
		std::cout << std::endl << "Pass " << trainingPass << std::endl;

		// Get new input data and feed it forward:
		if(traingData.getNextInputs(inputVals, currentImage) != topology[0]) {
			break;
		}
		traingData.showVectorVals(": Inputs:", inputVals);
		myNet.feedForward(inputVals);

		// Collect the net's actual output results:
		myNet.getResults(resultVals);
		traingData.showVectorVals("Outputs:", resultVals);
		std::cout << "Outputs Char: " << traingData.getCharFromOutputs(resultVals) << std::endl;

		// Train the net what the outputs should have been:
		traingData.getTargetOutputs(targetVals, currentImage);
		traingData.showVectorVals("Targets:", targetVals);
		std::cout << "Target Char: " << traingData.getChar(currentImage) << std::endl;
		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// Report how well the training is working, average over recent samples:
		std::cout << "Net recent average error: "
			<< myNet.getRecentAverageError() << std::endl;
	}

	myNet.exportNN("../Export/net.txt");
	std::cout << std::endl << "Done" << std::endl << std::endl;
	
	

	//End program
	std::cout << "Program ended, Press a key to continue\n";
	std::cin.ignore();
	return 0;
}
