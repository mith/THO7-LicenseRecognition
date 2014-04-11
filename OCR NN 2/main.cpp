#include <vector>
#include "basetimer.h"
#include "NeuralNetworkOCR.h"
#include "ImageList.h"

std::ostream& operator<< (std::ostream& stream, const std::vector<float>& fs)
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

	ocr.train(img_list, 1000 * 1000);

	int success = 0;

	for (int pass = 0; pass < 10; pass++) {
		auto img_data = img_list.getRandom();
		std::cout << "target char: " << img_data.first << std::endl;
		std::cout << "target output nodes: " << ocr.char_to_output(img_data.first) << std::endl;

		auto result = ocr.convert(img_data.second);
		std::cout << "output char: " << result.first << std::endl;
		std::cout << "output nodes: " << ocr.output_nodes() << std::endl;

		std::cout << "------------------------" << std::endl;

		if (result.first == img_data.first) {
			success++;
		}
	}
	std::cout << "Times success out of 10 passes: " << success;
	std::cin.ignore();
	return 0;
}