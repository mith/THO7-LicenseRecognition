#include <vector>
#include "NeuralNetwork.h"
#include "basetimer.h"
#include "ImageLib.h"


int main() {
	std::vector<unsigned int> topology({ 20, 30, 36 });

	NeuralNetwork net(topology);
	std::vector<float> input(20, 0.88f);

	BaseTimer tmr;
	tmr.start();
	for (int i = 0; i < 1000000; i++) {
		net.feedForward(input);
	}
	tmr.stop();

	std::cout << "feedforward took: " << tmr.elapsedSeconds() << std::endl;
	std::cin.ignore();
	return 0;
}