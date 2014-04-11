#include <vector>
#include "basetimer.h"
#include "NeuralNetworkOCR.h"
#include "ImageList.h"

std::ostream& operator<< (std::ostream& stream, const std::vector<double>& fs)
{
	stream << '[';

	for (int i = 0; i < fs.size() - 1; i++) {
		stream << fs[i] << ',';
	}

	stream << fs.back() << ']';

	return stream;
}

int main(int argc, const char* argv[])
{
	std::string img_dir = argv[1];

	ImageList img_list(img_dir);

	//NeuralNetworkOCR ocr("./Export/OCR.txt");
	NeuralNetworkOCR ocr;

	BaseTimer tmr;
	tmr.start();
	ocr.train(img_list, 2 * 1000 * 1000);
	tmr.stop();

	std::cout << "training took: " << tmr.elapsedSeconds() << " seconds." << std::endl;

	int success = 0;

	for (int pass = 0; pass < 10; pass++) {
		auto img_data = img_list.getRandom();
		std::cout << "filename: " << img_data.filename << std::endl;
		std::cout << "target char: " << img_data.getChar() << std::endl;
		std::cout << "target output nodes: " << ocr.char_to_output(img_data.getChar()) << std::endl;

		auto result = ocr.convert(img_data.image);
		std::cout << "output char: " << result.first << std::endl;
		std::cout << "output nodes: " << ocr.output_nodes() << std::endl;

		std::cout << "------------------------" << std::endl;

		if (result.first == img_data.getChar()) {
			success++;
		}
	}
	std::cout << "Times success out of 10 passes: " << success;
	std::cin.ignore();
	return 0;
}