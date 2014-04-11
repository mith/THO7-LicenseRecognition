#include "TrainingsManager.h"

int main(int argc, const char* argv[])
{
	TrainingsManager(argc > 1 ? argv[1] : "Images", "./Export/OCR.txt");

	std::cout << "Program ended, Press a key to continue\n";
	std::cin.ignore();
	return 0;
}