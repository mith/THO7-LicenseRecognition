#pragma once

#ifdef VISION_EXPORTS
#define VISIONDLL_API __declspec(dllexport) 
#else
#define VISIONDLL_API __declspec(dllimport) 
#endif

namespace vis {

	/**
	 * Class to hold a matrix.
	 */
	class Matrix {
	public:
		/**
		 * Will construct the Matrix using another Matrix. (Copy constructor)
		 * @param  other The Matrix to be copied.
		 */
		VISIONDLL_API Matrix(const Matrix &other);
		/**
		 * Construct a matrix from a file. Comma delimited and newlines.
		 * @param  file_name The name of the file the matrix is in.
		 */
		VISIONDLL_API Matrix(const char *file_name);
		/**
		 * Construct the Matrix from a float array.
		 * @param  columns The amount of columns of the matrix.
		 * @param  rows    The amount of columns of the matrix.
		 * @param  matrix  The float array containing the matrix. Single dimension!
		 */
		VISIONDLL_API Matrix(unsigned int columns, unsigned int rows, float *matrix = 0);
		/**
		 * Destroy the Matrix object and delete the float array.
		 */
		VISIONDLL_API ~Matrix() { delete[] m_Matrix; }

		/**
		 * Get the amount of columns in the Matrix
		 * @return Amount of columns
		 */
		VISIONDLL_API inline unsigned int GetColumns() const { return m_Matrix_columns; }
		/**
		 * Get the amount of rows in the Matrix
		 * @return Amount of rows
		 */
		VISIONDLL_API inline unsigned int GetRows() const { return m_Matrix_rows; }

		/**
		 * The total size(columns * rows)
		 * @return The size
		 */
		VISIONDLL_API unsigned int size() const { return m_Matrix_columns * m_Matrix_rows; };

		/**
		 * The subscript operator that offers the possibility to edit the Matrix.
		 * @param  index The index of the float array.
		 * @return       Return the float reference that you could edit.
		 */
		VISIONDLL_API inline float &operator[](int index) const { return m_Matrix[index]; }

		/**
		 * Get the inverse Matrix from this Matrix.
		 * @return Inversed Matrix
		 */
		VISIONDLL_API Matrix *GetInverse();
	private:
		float *m_Matrix;
		unsigned int m_Matrix_rows;
		unsigned int m_Matrix_columns;

		float GetDeterminant();
	};
}
/**
 * Multiply a Matrix with a float number.
 */
VISIONDLL_API vis::Matrix operator*(float lhs, const vis::Matrix &matrix);
VISIONDLL_API vis::Matrix operator*(const vis::Matrix &matrix, float lhs);

/**
 * Multiply two Matrices with eachother.
 */
VISIONDLL_API vis::Matrix operator*(const vis::Matrix &lhs, const vis::Matrix &rhs);
