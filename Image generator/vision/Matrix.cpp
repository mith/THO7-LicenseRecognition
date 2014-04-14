#include "stdafx.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <stdlib.h>		/* atof */

#include "Matrix.h"

namespace vis {
	Matrix::Matrix(const Matrix &other) {
		m_Matrix_columns = other.GetColumns();
		m_Matrix_rows = other.GetRows();

		m_Matrix = new float[m_Matrix_columns * m_Matrix_rows];
		for (unsigned int i = 0; i < other.size(); ++i) {
			m_Matrix[i] = other[i];
		}
	}
	Matrix::Matrix(const char *file_name) {
		std::vector<std::string> data;
		std::ifstream infile(file_name);

		unsigned int
			rows	= 0,
			columns	= 0;

		while (infile) {
			std::string s;
			if (!std::getline(infile, s)) {
				break;
			}

			std::istringstream ss(s);
			std::vector <std::string> record;

			// Keep old amount of columns to check later on if amount of columns are the same.
			unsigned int old_columns = columns;
			columns = 0;

			while (ss) {
				std::string s;
				if (!std::getline(ss, s, ',')) {
					break;
				}
				data.push_back(s);

				columns++;
			}
			// Check for different row sizes.
			if (old_columns != 0 && columns != old_columns) {}

			rows++;
			
		}

		m_Matrix_columns	= columns;
		m_Matrix_rows		= rows;

		m_Matrix = new float[columns * rows];

		for (unsigned int y = 0; y < rows; ++y) {
			for (unsigned int x = 0; x < columns; ++x) {
				m_Matrix[y * columns + x] = (float)atof(data.at(y * columns + x).c_str());
			}
		}

		/*for (int i = 0; i < data.size(); ++i) {
			std::cout << data.at(i) << std::endl;
		}*/
	}
	Matrix::Matrix(unsigned int columns, unsigned int rows, float *matrix) {
		m_Matrix_columns	= columns;
		m_Matrix_rows		= rows;

		if (matrix == 0) {
			m_Matrix = new float[columns * rows];
		} else {
			m_Matrix = matrix;
		}
	}
	Matrix *Matrix::GetInverse(){
		// Put values in simple variables for ease of use.
		float
			a = m_Matrix[0], b = m_Matrix[1], c = m_Matrix[2],
			d = m_Matrix[3], e = m_Matrix[4], f = m_Matrix[5],
			g = m_Matrix[6], h = m_Matrix[7], i = m_Matrix[8];

		//  Fill the adjugate matrix.
		float *af = new float[9];
		af[0] = (e * i - f * h);	af[1] = -(b * i - c * h);	af[2] = (b * f - c * e);
		af[3] = -(d * i - f * g);	af[4] = (a * i - c * g);	af[5] = -(a * f - c * d);
		af[6] = (d * h - e * g);	af[7] = -(a * h - b * g);	af[8] = (a * e - b * d);

		// Return the new Matrix, which is the inverse.
		return new Matrix(1 / this->GetDeterminant() * Matrix(3, 3, af)); // 1/det(a) * adj(a)
	}
	float Matrix::GetDeterminant() {
		float
			a = m_Matrix[0], b = m_Matrix[1], c = m_Matrix[2],
			d = m_Matrix[3], e = m_Matrix[4], f = m_Matrix[5],
			g = m_Matrix[6], h = m_Matrix[7], i = m_Matrix[8];
		return a * (e * i - f * h) - b * (i * d - f * g) - c * (d * h - e * h);
	}
}

vis::Matrix operator*(float lhs, const vis::Matrix &matrix) {
	vis::Matrix tmp(matrix.GetColumns(), matrix.GetRows());
	for (unsigned int i = 0; i < matrix.size(); ++i) {
		tmp[i] = lhs * matrix[i];
	}
	return tmp;
}
vis::Matrix operator*(const vis::Matrix &matrix, float lhs) {
	return lhs * matrix;
}
vis::Matrix operator*(const vis::Matrix &lhs, const vis::Matrix &rhs) {
	if (lhs.size() != 9 || lhs.GetRows() != 3 || rhs.size() != 9 || rhs.GetRows() != 3) {
		return vis::Matrix(3, 3, 0);
	}

	unsigned int rows = 3;
	unsigned int columns = 3;

	float *product = new float[9];
	memset(product, 0, rows * columns * sizeof(float));
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			// Multiply the row of A by the column of B to get the row, column of product.
			for (int inner = 0; inner < 3; inner++) {
				product[row * 3 + col] += lhs[row * 3 + inner] * rhs[inner * 3 + col];
			}
		}
	}

	return vis::Matrix(3, 3, product);
}