#include <vector>
#include "basetimer.h"
#include "NeuralNetworkOCR.h"
//#include "ImageList.h"
#include "TrainingsManager.h"

/*
std::ostream& operator<< (std::ostream& stream, const std::vector<double>& fs)
{
	stream << '[';

	for (int i = 0; i < fs.size() - 1; i++) {
		stream << fs[i] << ',';
	}

	stream << fs.back() << ']';

	return stream;
} */

int main(int argc, const char* argv[])
{
	NeuralNetworkOCR neuralnet;
	ImageLib::ImageGray img(argv[1]);
	std::vector<ImageGray> img_v;
	img_v.push_back(img);
	
	std::cout << "Character: " << neuralnet.recognise(img_v) << std::endl;

	// Uncomment code beneath for training, comment code above.

	//std::string img_dir(argc > 1 ? argv[1] : "ImagesNewDejshejs");
	//TrainData td(img_dir);
	//std::vector<std::vector<unsigned int>>  totalMistakes(td.getNumOutputs(), std::vector<unsigned int>(td.getNumOutputs(), 0));
	//for (unsigned int i = 0; i < 10; i++) {
	//	TrainingsManager t(td); //"./Export/NetExportTest1.txt"
	//	t.setTargetSuccesRate(0.99);
	//	t.run();
	//	t.saveWeights(("./Export/NetExport" + (std::string)(i + ".txt")));
	//	std::cout << "Last run had the following mistakes: " << std::endl;
	//	auto mistakes = t.getRecentMistakes();
	//	for (unsigned int t = 0; t < mistakes.size(); t++) {
	//		char target = t < 10 ? '0' + t : 'A' + (t - 10);
	//		if (target > 'Z') target = '-';
	//		for (unsigned int r = 0; r < mistakes.size(); r++) {
	//			if (!(mistakes[t][r] == 0)) {
	//				totalMistakes[t][r] += mistakes[t][r];
	//				char result = r < 10 ? '0' + r : 'A' + (r - 10);
	//				if (result > 'Z') result = '-';
	//				std::cout << target << " has been confused with " << result << " " << mistakes[t][r] << " times" << std::endl;
	//			}
	//		}
	//	}
	//}
	
	
		/*
	std::cout << std::endl << "------------------------" << std::endl;
	for (unsigned int t = 0; t < totalMistakes.size(); t++) {
		char target = t < 10 ? '0' + t : 'A' + (t - 10);
		if (target > 'Z') target = '-';
		for (unsigned int r = 0; r < totalMistakes.size(); r++) {
			if ((totalMistakes[t][r] > 1 )) {
				char result = r < 10 ? '0' + r : 'A' + (r - 10);
				if (result > 'Z') result = '-';
				std::cout << target << " has been confused with " << result << " " << totalMistakes[t][r] << " times" << std::endl;
			}
		}
	}*/
	std::cin.ignore();
	return 0;
}