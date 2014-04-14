#include <vector>
#include "basetimer.h"
//#include "NeuralNetworkOCR.h"
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
	std::string img_dir(argc > 1 ? argv[1] : "Images3600");
	TrainData td(img_dir);
	for (unsigned int i = 0; i < 10; i++) {
		TrainingsManager t(td, "./Export/NetExport1.txt");
		t.setTargetSuccesRate(0.999);
		t.run();
		t.saveWeights(("./Export/NetExport" + (std::string)(i + ".txt")));
		std::cout << "Last run had the following mistakes: " << std::endl;
		auto mistakes = t.getRecentMistakes();
		for (unsigned int t = 0; t < mistakes.size(); t++) {
			char target = t < 10 ? '0' + t : 'A' + (t - 10);
			for (unsigned int r = 0; r < mistakes.size(); r++) {
				if (!(mistakes[t][r] == 0)) {
					char result = r < 10 ? '0' + r : 'A' + (r - 10);
					std::cout << target << " has been confused with " << result << " " << mistakes[t][r] << " times" << std::endl;
				}
			}
		}
	}
	/*
	ImageList img_list(img_dir);

	std::cout << "loaded up" << std::endl;

	//NeuralNetworkOCR ocr("./Export/OCR.txt");
	//NeuralNetworkOCR ocr("OCR.txt");
	NeuralNetworkOCR ocr;

	BaseTimer tmr;
	tmr.start();
	ocr.train(img_list, 1 * 1000 * 1000);
	tmr.stop();

	ocr.export("OCR.txt");

	std::cout << "training took: " << tmr.elapsedSeconds() << " seconds." << std::endl;

	int success = 0;

	for (int pass = 0; pass < 1000; pass++) {
		auto img_data = img_list.getRandom();
		

		auto result = ocr.convert(img_data.image);
		

		if (result.first == img_data.getChar()) {
			success++;
		}
		else {
			std::cout << "filename: " << img_data.filename << std::endl;
			std::cout << "target char: " << img_data.getChar() << std::endl;
			std::cout << "target output nodes: " << ocr.char_to_output(img_data.getChar()) << std::endl;
			std::cout << "output char: " << result.first << std::endl;
			std::cout << "output nodes: " << ocr.output_nodes() << std::endl;

			std::cout << "------------------------" << std::endl;
		}
	} 

	std::cout << "Times success out of 1000 passes: " << success;
	*/
	std::cout << "Ending Program";
	std::cin.ignore();
	return 0;
}